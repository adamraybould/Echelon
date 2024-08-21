#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Entity.h"
#include "Graphics/Sprite.h"
#include "Graphics/SpriteSheet.h"
#include "Rendering/Renderer.h"

namespace Engine::ECS
{
    SpriteRenderer::SpriteRenderer(Entity& owner, Sprite& sprite) : Component(owner)
    {
        m_pSprite = &sprite;
        m_flipped = SDL_FLIP_NONE;
    }

    void SpriteRenderer::Initialize()
    {
    }

    void SpriteRenderer::Update(float delta)
    {
    }

    void SpriteRenderer::Render(Renderer& renderer)
    {
        // Ignore if no Sprite is Set
        if (m_pSprite == nullptr)
            return;

        Vector2 position = GetOwner().GetTransform().GetWorldPosition();
        float rotation = GetOwner().GetTransform().GetWorldRotation();
        Vector2 scale = GetOwner().GetTransform().GetWorldScale();

        Camera& camera = renderer.GetCamera();

        Vector2 screenPosition = camera.CalculateScreenPosition(position);

        SDL_Rect dest =
            {
            screenPosition.X - (m_pSprite->GetSource().Width * scale.X * 0.5f),
            screenPosition.Y - (m_pSprite->GetSource().Height * scale.Y * 0.5f),
                m_pSprite->GetSource().Width * scale.X,
                m_pSprite->GetSource().Height * scale.Y
            };

        SDL_Rect src = { m_pSprite->GetSource().X, m_pSprite->GetSource().Y, m_pSprite->GetSource().Width, m_pSprite->GetSource().Height };

        SDL_RenderCopyEx(renderer, &m_pSprite->GetRawTexture(), &src, &dest, rotation, NULL, static_cast<SDL_RendererFlip>(m_flipped));
    }

    void SpriteRenderer::Destroy()
    {
        m_pSprite = nullptr;
    }

    void SpriteRenderer::SetSpriteFrame(UInt frameIndex) const
    {
        SpriteSheet* spriteSheet = static_cast<SpriteSheet*>(m_pSprite);
        if (spriteSheet != nullptr)
        {
            Rectangle sourceRest = spriteSheet->GetSpriteSource(frameIndex);
            m_pSprite->SetSource(sourceRest);
        }
    }
}
