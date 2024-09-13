#ifndef PARTICLE_H
#define PARTICLE_H
#include "Core/TypeDefs.h"
#include "Core/Maths/Vector2.h"

namespace Core { class Renderer; }

using namespace Core;
namespace Graphics
{
    class Texture2D;
    class Sprite;

    class Particle
    {
    private:
        Sprite& m_sprite;

        Vector2F m_position;
        Vector2F m_screenPosition;

        Vector2F m_velocity;
        float m_rotation;
        Vector2F m_scale;

        float m_speed;
        UInt m_lifetime;
        bool m_isActive;

    public:
        Particle(Texture2D& texture, UInt lifetime, float speed);
        ~Particle() = default;

        void Update(float delta);
        void Render(Renderer& renderer) const;

        void SetPosition(const Vector2F position) { m_position = position; }
        void SetVelocity(const Vector2F velocity) { m_velocity = velocity; }
        void SetRotation(const float rotation) { m_rotation = rotation; }
        void SetScale(const Vector2F scale) { m_scale = scale; }

        void SetLifeTime(const UInt lifeTime) { m_lifetime = lifeTime; }
        void SetSpeed(const float speed) { m_speed = speed; }
        void Reset(const Vector2F& position, UInt lifetime, float speed);

        void SetActive(const bool value) { m_isActive = value; }
        bool IsActive () const { return m_isActive; }

        Vector2F GetScreenPosition() const { return m_screenPosition; }

        Sprite& GetSprite() const { return m_sprite; }
        Vector2F& GetPosition() { return m_position; }
        float& GetRotation() { return m_rotation; }
        Vector2F& GetScale () { return m_scale; }

        bool IsDead() const;
        bool IsOffScreen() const;
    };
}

#endif //PARTICLE_H
