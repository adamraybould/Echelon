#include "Scene/Entities/Components/SpriteRenderer.h"
#include <SDL2/SDL_render.h>

#include "Core/IO/Renderer.h"
#include "Core/AssetManager.h"
#include "Scene/Entities/Entity.h"
#include "Graphics/SpriteSheet.h"
#include "Core//Scripting/Prefab.h"
#include "Core/Constants.h"

namespace Scene
{
    namespace Components
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
            const Rectangle bounds = GetOwner().GetBounds();
            const Vector2F scale = GetOwner().GetTransform().Scale;

            if (m_pSprite != nullptr)
            {
                m_spriteScale = Vector2F((m_source.Width * scale.X) * SPRITE_SCALE, (m_source.Height * scale.Y) * SPRITE_SCALE);
                GetOwner().SetBounds(RectI(bounds.X, bounds.Y, m_spriteScale.X * 0.5f, m_spriteScale.Y));
            }
        }

        void SpriteRenderer::Render(Renderer& renderer)
        {
            if (m_pSprite == nullptr)
                return;

            Vector2F position = GetOwner().GetTransform().GetWorldPosition();
            float rotation = GetOwner().GetTransform().GetWorldRotation();

            Camera& camera = renderer.GetCamera();
            Vector2F screenPosition = camera.CalculateScreenPosition(position);

            SDL_Rect src = m_source;
            SDL_Rect dest = { screenPosition.X - m_spriteScale.X * 0.5f, screenPosition.Y - m_spriteScale.Y * 0.5f, m_spriteScale.X, m_spriteScale.Y };

            SDL_RenderCopyEx(renderer, &m_pSprite->GetRawTexture(), &src, &dest, rotation, nullptr, static_cast<SDL_RendererFlip>(m_flipped));
        }

        void SpriteRenderer::Destroy()
        {
            m_pSprite = nullptr;
        }

        void SpriteRenderer::SetSourceFromFrame(const UInt frameIndex)
        {
            SpriteSheet* spriteSheet = static_cast<SpriteSheet*>(m_pSprite);
            if (spriteSheet != nullptr)
            {
                RectI sourceRect = spriteSheet->GetSpriteSource(frameIndex);
                m_source = sourceRect;
            }
        }

        void SpriteRenderer::SetDisplaySource(const int x, const int y, const int width, const int height)
        {
            m_source = RectI(x, y, width, height);
        }

        Sprite& SpriteRenderer::GetSprite() const
        {
            return *m_pSprite;
        }
    }
}
