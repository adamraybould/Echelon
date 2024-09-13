#include "Scene/Entities/Components/SpriteRenderer.h"
#include <SDL2/SDL_render.h>

#include "Core/IO/Renderer.h"
#include "Core/AssetManager.h"
#include "Scene/Entities/Entity.h"
#include "Graphics/SpriteSheet.h"
#include "Core//Scripting/Prefab.h"
#include "Core/Constants.h"
#include "Graphics/Sprite.h"

namespace Scene
{
    namespace Components
    {
        SpriteRenderer::SpriteRenderer(Entity& owner) : Component(owner)
        {
            m_pSprite = nullptr;
            m_flipped = SDL_FLIP_NONE;

            SetRenderLayer(RenderLayer::Default);
            Renderer::AddToRenderQueue(*this);
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
                const String path = spriteAsset->GetPath();
                const int param = spriteAsset->GetParam();

                //m_pSprite = AssetManager::LoadSpriteSheet(path.c_str());
                Texture2D& texture = AssetManager::LoadSpriteSheet(path);
                m_pSprite = &Renderer::CreateSprite(texture);
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
            const Vector2F scale = GetOwner().GetTransform().GetWorldScale();

            if (m_pSprite != nullptr)
            {
                m_spriteScale = Vector2F((m_source.Width * scale.X) * SPRITE_SCALE, (m_source.Height * scale.Y) * SPRITE_SCALE);
                GetOwner().SetBounds(RectF(bounds.X, bounds.Y, m_spriteScale.X * 0.5f, m_spriteScale.Y));
            }
        }

        void SpriteRenderer::Render(Renderer& renderer)
        {
            const Vector2F position = GetOwner().GetTransform().GetWorldPosition();
            const float rotation = GetOwner().GetTransform().GetWorldRotation();

            const RectF src = m_source;
            const RectF dest = { position.X, position.Y, m_spriteScale.X, m_spriteScale.Y };

            renderer.Render(m_pSprite, src, dest, rotation);
        }

        float SpriteRenderer::GetDepth()
        {
            return GetOwner().GetTransform().Position.Y;
        }

        void SpriteRenderer::Destroy()
        {
            m_pSprite = nullptr;
        }

        void SpriteRenderer::SetSourceFromFrame(const UInt frameIndex)
        {
            const SpriteSheet* spriteSheet = static_cast<SpriteSheet*>(&m_pSprite->GetMaterial().GetTexture());
            if (spriteSheet != nullptr)
            {
                RectF sourceRect = spriteSheet->GetSpriteSource(frameIndex);
                m_source = sourceRect;
            }
        }

        void SpriteRenderer::SetDisplaySource(const int x, const int y, const int width, const int height)
        {
            m_source = RectF(x, y, width, height);
        }

        Sprite& SpriteRenderer::GetSprite() const
        {
            return *m_pSprite;
        }
    }
}
