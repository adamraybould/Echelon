#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Entity.h"
#include "Graphics/Sprite.h"
#include <SDL.h>

#include "Graphics/SpriteSheet.h"

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

    void SpriteRenderer::Render(SDL_Renderer& renderer)
    {
        // Ignore if no Sprite is Set
        if (m_pSprite == nullptr)
            return;

        Transform& transform = GetOwner().Transform();

        SDL_Rect dest = { transform.Position.X, transform.Position.Y, m_pSprite->GetSource().Width * transform.Scale.X, m_pSprite->GetSource().Height * transform.Scale.Y };
        SDL_Rect src = { m_pSprite->GetSource().X, m_pSprite->GetSource().Y, m_pSprite->GetSource().Width, m_pSprite->GetSource().Height };

        SDL_RenderCopyEx(&renderer, &m_pSprite->GetRawTexture(), &src, &dest, transform.Rotation, NULL, (SDL_RendererFlip)m_flipped);
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
