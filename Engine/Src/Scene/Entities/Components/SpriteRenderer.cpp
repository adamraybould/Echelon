#include "Scene/Entities/Components/SpriteRenderer.h"
#include <SDL2/SDL_render.h>

#include "Core/IO/Renderer.h"
#include "Core/AssetManager.h"
#include "Scene/Entities/Entity.h"
#include "Graphics/SpriteSheet.h"
#include "Core//Scripting/Prefab.h"
#include "Core/Constants.h"
#include "Graphics/Material.h"
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
            BindFunction<SpriteRenderer>(L, "SetFrame", &SpriteRenderer::SetFrame);
        }

        void SpriteRenderer::Initialize()
        {
            PrefabAsset* spriteAsset = GetPrefabAsset(AssetType::SPRITE);
            if (spriteAsset != nullptr)
            {
                const String path = spriteAsset->GetPath();
                const int param = spriteAsset->GetParam();

                m_pSpriteSheet = &AssetManager::LoadSpriteSheet(path);
                m_pSprite = &Renderer::CreateSprite(*m_pSpriteSheet);

                const RectU firstFrame = m_pSpriteSheet->GetFrame(0);
                SetFrameSource(0, 0, firstFrame.Width,firstFrame.Height);
                if (spriteAsset->HasParams())
                {
                    SetFrame(param);
                }
            }
        }

        void SpriteRenderer::Render(Renderer& renderer)
        {
            const Vector2F position = GetOwner().GetTransform().GetWorldPosition();
            const float rotation = GetOwner().GetTransform().GetWorldRotation();
            const Vector2F scale = GetOwner().GetTransform().GetWorldScale();

            const Vector2F worldScale = Vector2F((m_src.Width * scale.X) * SPRITE_SCALE, (m_src.Height * scale.Y) * SPRITE_SCALE);
            m_dest = { position.X, position.Y, worldScale.X, worldScale.Y };

            renderer.Render(m_pSprite, m_src, m_dest, rotation);
        }

        float SpriteRenderer::GetDepth()
        {
            return GetOwner().GetTransform().Position.Y;
        }

        void SpriteRenderer::Destroy()
        {
            m_pSprite = nullptr;
        }

        void SpriteRenderer::SetFrame(const UInt index)
        {
            if (m_pSpriteSheet != nullptr)
            {
                const RectU source = m_pSpriteSheet->GetFrame(index);
                SetFrameSource(source);
            }
        }

        void SpriteRenderer::SetFrameSource(const UInt x, const UInt y, const UInt width, const UInt height)
        {
            m_src = RectF(x, y, width, height);
        }

        void SpriteRenderer::SetFrameSource(const RectU source)
        {
            SetFrameSource(source.X, source.Y, source.Width, source.Height);
        }
    }
}
