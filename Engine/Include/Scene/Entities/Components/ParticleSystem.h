#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Component.h"
#include "Core/Commons.h"
#include "Core/Maths/Vector2.h"
#include "Core/Utility.h"
#include "Rendering/Renderable.h"

constexpr int MAX_PARTICLES = 200;

namespace Graphics { class Particle; class ParticleEmitter; class Texture2D; }

namespace Scene
{
    namespace Components
    {
        class ParticleSystem final : public Component, public Rendering::Renderable
        {
        private:
            UniquePtr<Graphics::ParticleEmitter> m_pEmitter;

            Array<UniquePtr<Graphics::Particle>> m_pParticles;
            Array<UniquePtr<Graphics::Particle>> m_pActiveParticles;

            UInt m_currentActiveParticles = 0;

            Random m_random;

            Graphics::Texture2D* m_pTexture;
            Vector2F m_velocity;
            Vector2F m_scale;

            UInt m_particleCount = 0;
            MinMaxRangeU m_particleLifetime;
            MinMaxRangeF m_particleSpeed;

        public:
            explicit ParticleSystem(Entity& owner);
            ~ParticleSystem() override;
            void SetupEmbedding(lua_State* L) override;

            void Initialize() override;
            void Update(float delta) override;
            void Render(Renderer& renderer) override;

            void SpawnParticle(const Vector2F& position);

            // -- Particle Emitters
            void CreateCircleEmitter(UInt emissionRate, float radius);
            void CreateLineEmitter(UInt emissionRate, float startX, float startY, float endX, float endY);
            void CreateBoxEmitter(UInt emissionRate, float x, float y, float width, float height);

            void SetVelocity(const float x, const float y) { m_velocity = Vector2F(x, y); }
            void SetScale(const float scale) { m_scale = Vector2F(scale, scale); }

            void SetParticleTexture(const String& texturePath);
            void SetMaxParticleCount(const UInt count) { m_particleCount = count; }
            void SetParticleLifetime(const UInt min, const UInt max) { m_particleLifetime = MinMaxRangeU(min, max); }
            void SetParticleSpeed(const float min, const float max) { m_particleSpeed = MinMaxRangeF(min, max); }

            UInt GetParticleCount() const { return m_particleCount; }

        private:
            bool IsParticleSystemInitialized() const { return m_pEmitter != nullptr; }

            Vector2F GetRandomParticlePosition() const;
            float GetRandomParticleLifetime();
            float GetRandomParticleSpeed();
        };
    }
}

#endif //PARTICLESYSTEM_H
