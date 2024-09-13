#include "Graphics/Particle.h"

#include "Core/IO/Renderer.h"
#include "Graphics/Sprite.h"

namespace Graphics
{
    Particle::Particle(Texture2D& texture, const UInt lifetime, const float speed) : m_sprite(Renderer::CreateSprite(texture))
    {
        m_position = Vector2F::Zero();
        m_rotation = 0.0f;

        m_lifetime = lifetime;
        m_speed = speed;

        m_isActive = true;
    }

    void Particle::Update(const float delta)
    {
        m_position += m_velocity * (m_speed * delta);
    }

    void Particle::Render(Renderer& renderer) const
    {
        RectF src = { 0, 0, static_cast<float>(m_sprite.GetWidth()), static_cast<float>(m_sprite.GetHeight()) };
        RectF dest = RectF(m_position.X, m_position.Y, m_sprite.GetWidth() * m_scale.X, m_sprite.GetHeight() * m_scale.Y);
        renderer.Render(&m_sprite, src, dest, 0.0f);
    }

    void Particle::Reset(const Vector2F& position, const UInt lifetime, const float speed)
    {
        SetPosition(position);
        m_lifetime = lifetime;
        m_speed = speed;

        m_lifetime = (SDL_GetTicks() * 0.001f) + lifetime;
    }

    bool Particle::IsDead() const
    {
        return SDL_GetTicks() * 0.001f >= m_lifetime || IsOffScreen();
    }

    bool Particle::IsOffScreen() const
    {
        const RectF& viewport = Camera::Main->GetViewport();
        return !viewport.ContainsPoint(m_position);
    }
}
