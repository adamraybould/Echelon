#include "Scene/Entities/Components/ParticleSystem.h"

#include "Core/AssetManager.h"
#include "Core/IO/Renderer.h"
#include "Graphics/ParticleEmitter.h"
#include "Graphics/Particle.h"
#include "Scene/Entities/Entity.h"

using namespace Graphics;
namespace Scene
{
    namespace Components
    {
        ParticleSystem::ParticleSystem(Entity& owner) : Component(owner)
        {
            m_pTexture = nullptr;

            m_velocity = Vector2F::Zero();
            m_scale = Vector2F::One();

            SetRenderLayer(RenderLayer::Default);
            Renderer::AddToRenderQueue(*this);
        }

        void ParticleSystem::SetupEmbedding(lua_State* L)
        {
            Component::SetupEmbedding(L);

            BindClass<ParticleSystem>(L);

            BindFunction<ParticleSystem>(L, "CreateCircleEmitter", &ParticleSystem::CreateCircleEmitter);
            BindFunction<ParticleSystem>(L, "CreateLineEmitter", &ParticleSystem::CreateLineEmitter);
            BindFunction<ParticleSystem>(L, "CreateBoxEmitter", &ParticleSystem::CreateBoxEmitter);

            BindFunction<ParticleSystem>(L, "SetVelocity", &ParticleSystem::SetVelocity);
            BindFunction<ParticleSystem>(L, "SetScale", &ParticleSystem::SetScale);

            BindFunction<ParticleSystem>(L, "SetParticleTexture", &ParticleSystem::SetParticleTexture);
            BindFunction<ParticleSystem>(L, "SetMaxParticleCount", &ParticleSystem::SetMaxParticleCount);
            BindFunction<ParticleSystem>(L, "SetParticleLifetime", &ParticleSystem::SetParticleLifetime);
            BindFunction<ParticleSystem>(L, "SetParticleSpeed", &ParticleSystem::SetParticleSpeed);
        }

        ParticleSystem::~ParticleSystem()
        {
            for (auto& particle : m_pParticles)
            {
                particle.reset();
            }

            m_pParticles.clear();
        }

        void ParticleSystem::Initialize()
        {
            if (IsParticleSystemInitialized())
            {
                m_pParticles.clear();

                // Create Particles initially
                for (UInt i = 0; i < m_particleCount; ++i)
                {
                    UniquePtr<Particle> particle = std::make_unique<Particle>(*m_pTexture, GetRandomParticleLifetime(), GetRandomParticleSpeed());
                    particle->SetVelocity(m_velocity);
                    particle->SetScale(m_scale);
                    particle->SetActive(false);

                    m_pParticles.push_back(std::move(particle));
                }
            }
        }

        void ParticleSystem::Update(const float delta)
        {
            if (m_pEmitter != nullptr && m_currentActiveParticles < m_particleCount)
            {
                m_pEmitter->EmitParticles(*this, delta);
            }

            for (UInt i = 0; i < m_currentActiveParticles; i++)
            {
                const auto& particle = m_pParticles[i];
                particle->Update(delta);

                if (particle->IsDead())
                {
                    particle->Reset(GetRandomParticlePosition(), GetRandomParticleLifetime(), GetRandomParticleSpeed());
                }
            }
        }

        void ParticleSystem::Render(Renderer& renderer)
        {
            for (UInt i = 0; i < m_currentActiveParticles; i++)
            {
                const auto& particle = m_pParticles[i];
                particle->Render(renderer);
            }
        }

        void ParticleSystem::SpawnParticle(const Vector2F& position)
        {
            if (m_pParticles.empty())
                return;

            if (m_currentActiveParticles >= m_particleCount)
                return;

            const auto& particle = m_pParticles[m_currentActiveParticles++];
            particle->Reset(position, GetRandomParticleLifetime(), GetRandomParticleSpeed());
            particle->SetActive(true);
        }

        void ParticleSystem::CreateCircleEmitter(const UInt emissionRate, const float radius)
        {
            m_pEmitter = ParticleEmitter::CreateCircleEmitter(emissionRate, radius);
        }

        void ParticleSystem::CreateLineEmitter(const UInt emissionRate, const float startX, const float startY, const float endX, const float endY)
        {
            m_pEmitter = ParticleEmitter::CreateLineEmitter(emissionRate, Vector2F(startX, startY), Vector2F(endX, endY));
        }

        void ParticleSystem::CreateBoxEmitter(const UInt emissionRate, const float x, const float y, const float width, const float height)
        {
            m_pEmitter = ParticleEmitter::CreateBoxEmitter(emissionRate, x, y, width, height);
        }

        void ParticleSystem::SetParticleTexture(const String& texturePath)
        {
            m_pTexture = &AssetManager::LoadTexture(texturePath);
        }

        Vector2F ParticleSystem::GetRandomParticlePosition() const
        {
            if (m_pEmitter == nullptr)
            {
                std::cerr << "No Particle Emitter Set" << std::endl;
                return Vector2F::Zero();
            }

            return GetOwner().GetTransform().GetWorldPosition() + m_pEmitter->GetRandomPosition();
        }

        float ParticleSystem::GetRandomParticleLifetime()
        {
            return m_random.GetInt(m_particleLifetime.Min, m_particleLifetime.Max);
        }

        float ParticleSystem::GetRandomParticleSpeed()
        {
            return m_random.GetFloat(m_particleSpeed.Min, m_particleSpeed.Max);
        }
    }
}
