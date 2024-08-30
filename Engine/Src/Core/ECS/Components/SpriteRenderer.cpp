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
        BindFunction<SpriteRenderer>(L, "SetFrame", &SpriteRenderer::SetSpriteFrame);
    }

    void SpriteRenderer::Initialize()
    {
        if (GetOwner().HasPrefab())
        {
            Prefab& prefab = GetOwner().GetPrefab();
            PrefabAsset* spriteAsset = prefab.GetAsset(SPRITE);
            if (spriteAsset != nullptr)
            {
                String path = spriteAsset->GetPath();
                int param = spriteAsset->GetParam();

                SpriteSheet& spriteSheet = AssetManager::LoadSpriteSheet(path.c_str());
                m_pSprite = &spriteSheet;

                if (spriteAsset->HasParams())
                {
                    SetSpriteFrame(param);
                }
            }
        }
    }

    void SpriteRenderer::Update(float delta)
    {
        Rectangle bounds = GetOwner().GetBounds();
        Vector2 scale = GetOwner().GetTransform().Scale;

        if (m_pSprite != nullptr)
        {
            m_spriteScale = Vector2((m_pSprite->GetSource().Width * scale.X) * SPRITE_SCALE, (m_pSprite->GetSource().Height * scale.Y) * SPRITE_SCALE);
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

        SDL_Rect src = { m_pSprite->GetSource().X, m_pSprite->GetSource().Y, m_pSprite->GetSource().Width, m_pSprite->GetSource().Height };

        SDL_RenderCopyEx(renderer, &m_pSprite->GetRawTexture(), &src, &dest, rotation, NULL, static_cast<SDL_RendererFlip>(m_flipped));
    }

    void SpriteRenderer::Destroy()
    {
        m_pSprite = nullptr;
    }

    void SpriteRenderer::SetSpriteFrame(int frameIndex) const
    {
        SpriteSheet* spriteSheet = static_cast<SpriteSheet*>(m_pSprite);
        if (spriteSheet != nullptr)
        {
            Rectangle sourceRect = spriteSheet->GetSpriteSource(frameIndex);
            m_pSprite->SetSource(sourceRect);
        }
    }

    Sprite& SpriteRenderer::GetSprite() const
    {
        return *m_pSprite;
    }
}
