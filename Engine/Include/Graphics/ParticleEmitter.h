#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H
#include "Core/TypeDefs.h"
#include "Core/Utility.h"
#include "Core/Maths/Vector2.h"
#include "Core/Maths/Rectangle.h"
#include "Core/Scripting/IBinder.h"

namespace Scene::Components { class ParticleSystem; }

namespace Graphics
{
    class ParticleEmitter
    {
    protected:
        static Random m_random;

        UInt m_emissionRate = 0;
        float m_emissionTimer = 1.0f;

    public:
        explicit ParticleEmitter(UInt emissionRate);
        virtual ~ParticleEmitter() = default;
        virtual Vector2F GetRandomPosition() const = 0;

        void EmitParticles(Scene::Components::ParticleSystem& particleSystem, float delta);

        static UniquePtr<ParticleEmitter> CreateCircleEmitter(UInt emissionRate, float radius);
        static UniquePtr<ParticleEmitter> CreateLineEmitter(UInt emissionRate, const Vector2F& start, const Vector2F&  end);
        static UniquePtr<ParticleEmitter> CreateBoxEmitter(UInt emissionRate, float x, float y, float width, float height);
    };

    class CircleEmitter final : public ParticleEmitter
    {
    private:
        float m_radius;

    public:
        CircleEmitter(const UInt emissionRate, const float radius) : ParticleEmitter(emissionRate), m_radius(radius) {}

        Vector2F GetRandomPosition() const override
        {
            float angle = m_random.GetFloat(0.0f, 2.0f * M_PI);
            float radius = std::sqrt(m_random.GetFloat01() * m_radius);

            return { std::cos(angle) * radius, std::sin(angle) * radius };
        }
    };

    class LineEmitter final : public ParticleEmitter
    {
    private:
        const Vector2F& m_start;
        const Vector2F& m_end;

    public:
        LineEmitter(const UInt emissionRate, const Vector2F& start, const Vector2F& end) : ParticleEmitter(emissionRate), m_start(start), m_end(end) {}

        Vector2F GetRandomPosition() const override
        {
            float t = m_random.GetFloat01();
            return Vector2F::Lerp(m_start, m_end, t);
        }
    };

    class BoxEmitter final : public ParticleEmitter
    {
    private:
        float m_x;
        float m_y;
        float m_width;
        float m_height;

    public:
        BoxEmitter(const UInt emissionRate, const float x, const float y, const float width, const float height) : ParticleEmitter(emissionRate), m_x(x), m_y(y), m_width(width), m_height(height) {}

        Vector2F GetRandomPosition() const override
        {
            float x = m_random.GetFloat(m_x - m_width * 0.5f, m_x + m_width * 0.5f);
            float y = m_random.GetFloat(m_y - m_height * 0.5f, m_y + m_height * 0.5f);
            return { x, y };
        }
    };
}

#endif //PARTICLEEMITTER_H
