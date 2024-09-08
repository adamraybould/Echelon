#include "Graphics/ParticleEmitter.h"

#include "Core/Constants.h"
#include "Scene/Entities/Entity.h"
#include "Scene/Entities/Components/ParticleSystem.h"

using namespace Scene::Components;
namespace Graphics
{
    Random ParticleEmitter::m_random;

    ParticleEmitter::ParticleEmitter(const UInt emissionRate)
    {
        m_emissionRate = emissionRate;
    }

    void ParticleEmitter::EmitParticles(ParticleSystem& particleSystem, const float delta)
    {
        m_emissionTimer += delta;
        if (m_emissionTimer >= 1.0f) // 1 Second
        {
            m_emissionTimer = 0.0f;

            for (UInt i = 0; i < m_emissionRate; i++)
            {
                Vector2F systemPos = particleSystem.GetOwner().GetTransform().GetWorldPosition();
                particleSystem.SpawnParticle(systemPos + GetRandomPosition());
            }
        }
    }

    UniquePtr<ParticleEmitter> ParticleEmitter::CreateCircleEmitter(UInt emissionRate, const float radius)
    {
        return std::make_unique<CircleEmitter>(emissionRate, radius * PPM);
    }

    UniquePtr<ParticleEmitter> ParticleEmitter::CreateLineEmitter(UInt emissionRate, const Vector2F& start, const Vector2F& end)
    {
        return std::make_unique<LineEmitter>(emissionRate, start, end);
    }

    UniquePtr<ParticleEmitter> ParticleEmitter::CreateBoxEmitter(UInt emissionRate, float x, float y, float width, float height)
    {
        return std::make_unique<BoxEmitter>(emissionRate, x, y, width, height);
    }
}
