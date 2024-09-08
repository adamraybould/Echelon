#include "Graphics/Particle.h"
#include "Graphics/Texture2D.h"
#include "Core/IO/Renderer.h"

namespace Graphics
{
    Particle::Particle(Texture2D& texture, const UInt lifetime, const float speed) : m_texture(texture)
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
        m_screenPosition = Camera::Main->CalculateScreenPosition(m_position);
    }

    void Particle::Render(const Renderer& renderer) const
    {
        SDL_Rect src = { 0, 0, m_texture.GetWidth(), m_texture.GetHeight() };
        SDL_Rect dest = RectF(m_screenPosition.X, m_screenPosition.Y, m_texture.GetWidth() * m_scale.X, m_texture.GetHeight() * m_scale.Y);
        SDL_RenderCopyEx(renderer, &m_texture.GetRawTexture(), &src, &dest, m_rotation, nullptr, SDL_FLIP_NONE);
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
        const RectI& viewport = Camera::Main->GetViewport();
        return m_screenPosition.X < viewport.X || m_screenPosition.X > viewport.X + viewport.Width || m_screenPosition.Y < viewport.Y || m_screenPosition.Y > viewport.Y + viewport.Height;
    }
}