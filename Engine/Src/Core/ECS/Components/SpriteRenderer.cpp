#include "Engine/Core/ECS/Components/SpriteRenderer.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Graphics/SpriteSheet.h"
#include "Engine/Core/Renderer.h"
#include <SDL_render.h>

namespace Core::Components
{
    SpriteRenderer::SpriteRenderer(Entity& owner, Sprite& sprite) : Component(owner), m_sprite(sprite)
    {
        m_flipped = SDL_FLIP_NONE;
    }

    void SpriteRenderer::Initialize()
    {
    }

    void SpriteRenderer::Update(float delta)
    {
        Rectangle bounds = GetOwner().GetBounds();
        Vector2 scale = GetOwner().GetTransform().Scale;
        GetOwner().SetBounds(Rectangle(bounds.X, bounds.Y, m_sprite.GetSource().Width * scale.X * 0.5f, m_sprite.GetSource().Height * scale.Y));
    }

    void SpriteRenderer::Render(Renderer& renderer)
    {
        Vector2 position = GetOwner().GetTransform().GetWorldPosition();
        float rotation = GetOwner().GetTransform().GetWorldRotation();
        Vector2 scale = GetOwner().GetTransform().GetWorldScale();

        Camera& camera = renderer.GetCamera();
        Vector2 screenPosition = camera.CalculateScreenPosition(position);

        SDL_Rect dest =
            {
            screenPosition.X - (m_sprite.GetSource().Width * scale.X * 0.5f),
            screenPosition.Y - (m_sprite.GetSource().Height * scale.Y * 0.5f),
                m_sprite.GetSource().Width * scale.X,
                m_sprite.GetSource().Height * scale.Y
            };

        SDL_Rect src = { m_sprite.GetSource().X, m_sprite.GetSource().Y, m_sprite.GetSource().Width, m_sprite.GetSource().Height };

        SDL_RenderCopyEx(renderer, &m_sprite.GetRawTexture(), &src, &dest, rotation, NULL, static_cast<SDL_RendererFlip>(m_flipped));
    }

    void SpriteRenderer::Destroy()
    {
        m_sprite = nullptr;
    }

    void SpriteRenderer::SetSpriteFrame(UInt frameIndex) const
    {
        SpriteSheet* spriteSheet = static_cast<SpriteSheet*>(&m_sprite);
        if (spriteSheet != nullptr)
        {
            Rectangle sourceRest = spriteSheet->GetSpriteSource(frameIndex);
            m_sprite.SetSource(sourceRest);
        }
    }

    Sprite& SpriteRenderer::GetSprite() const
    {
        return m_sprite;
    }
}
