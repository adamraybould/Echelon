#include "Engine/Core/ECS/Components/SpriteRenderer.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Graphics/SpriteSheet.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/Scripting/Prefab.h"
#include "Engine/Graphics/AssetManager.h"
#include "Engine/Utility/Constants.h"
#include <SDL_render.h>

namespace Core::Components
{
    SpriteRenderer::SpriteRenderer(Entity& owner) : Component(owner)
    {
        m_pSprite = nullptr;
        m_flipped = SDL_FLIP_NONE;
    }

    void SpriteRenderer::SetupEmbedding(lua_State* L)
    {
        Component::SetupEmbedding(L);

        BindClass<SpriteRenderer>(L);
        BindFunction<SpriteRenderer>(L, "SetFrame", &SpriteRenderer::SetSourceFromFrame);
    }

    void SpriteRenderer::Initialize()
    {
        PrefabAsset* spriteAsset = GetPrefabAsset(AssetType::SPRITE);
        if (spriteAsset != nullptr)
        {
            String path = spriteAsset->GetPath();
            int param = spriteAsset->GetParam();

            m_pSprite = AssetManager::LoadSpriteSheet(path.c_str());
            m_source = { 0, 0, m_pSprite->GetWidth(), m_pSprite->GetHeight() };

            if (spriteAsset->HasParams())
            {
                SetSourceFromFrame(param);
            }
        }
    }

    void SpriteRenderer::Update(float delta)
    {
        Rectangle bounds = GetOwner().GetBounds();
        Vector2 scale = GetOwner().GetTransform().Scale;

        if (m_pSprite != nullptr)
        {
            m_spriteScale = Vector2((m_source.Width * scale.X) * SPRITE_SCALE, (m_source.Height * scale.Y) * SPRITE_SCALE);
            GetOwner().SetBounds(Rectangle(bounds.X, bounds.Y, m_spriteScale.X * 0.5f, m_spriteScale.Y));
        }
    }

    void SpriteRenderer::Render(Renderer& renderer)
    {
        if (m_pSprite == nullptr)
            return;

        Vector2 position = GetOwner().GetTransform().GetWorldPosition();
        float rotation = GetOwner().GetTransform().GetWorldRotation();
        Vector2 scale = GetOwner().GetTransform().GetWorldScale();

        Camera& camera = renderer.GetCamera();
        Vector2 screenPosition = camera.CalculateScreenPosition(position);
        screenPosition = Vector2(screenPosition.X, screenPosition.Y);

        SDL_Rect dest =
            {
            screenPosition.X - (m_spriteScale.X * 0.5f),
            screenPosition.Y - (m_spriteScale.Y * 0.5f),
            m_spriteScale.X,
            m_spriteScale.Y,
            };

        SDL_Rect src = { m_source.X, m_source.Y, m_source.Width, m_source.Height };

        SDL_RenderCopyEx(renderer, &m_pSprite->GetRawTexture(), &src, &dest, rotation, NULL, static_cast<SDL_RendererFlip>(m_flipped));
    }

    void SpriteRenderer::Destroy()
    {
        m_pSprite = nullptr;
    }

    void SpriteRenderer::SetSourceFromFrame(UInt frameIndex)
    {
        SpriteSheet* spriteSheet = static_cast<SpriteSheet*>(m_pSprite);
        if (spriteSheet != nullptr)
        {
            Rectangle sourceRect = spriteSheet->GetSpriteSource(frameIndex);
            m_source = sourceRect;
        }
    }

    void SpriteRenderer::SetDisplaySource(const UInt x, const UInt y, const UInt width, const UInt height)
    {
        m_source = Rectangle(x, y, width, height);
    }

    Sprite& SpriteRenderer::GetSprite() const
    {
        return *m_pSprite;
    }
}
