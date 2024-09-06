#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "Component.h"
#include "Core/Maths/Vector2.h"

class b2Body;

namespace Core
{
    namespace Components
    {
        class Rigidbody : public Component
        {
            enum class BodyType
            {
                STATIC,
                DYNAMIC
            };

        private:
            b2Body* m_pBody = nullptr;
            BodyType m_bodyType = BodyType::STATIC;

            float m_linearDamping = 40.0f;
            float m_angularDamping = 0.5f;

        public:
            Rigidbody(Entity& owner);
            ~Rigidbody() override;

            void SetupEmbedding(lua_State* L) override;

            void Initialize() override;
            void Update(float delta) override;
            void Render(Renderer& renderer) override;
            void Destroy() override;

            void CreateStaticBody();
            void CreateDynamicBody();

            void SetLinearDamping(const float value) { m_linearDamping = value; }
            void SetAngularDamping(const float value) { m_angularDamping = value; }

            void ApplyForce(const LRef& force) const;
            void ApplyImpulse(LRef force) const;

            void SetPosition(const Vector2F& position) const;
            void SetPositionL(const LRef& position) const;

        private:
            void CreateBody();
            Vector2F GetSpriteSize() const;
        };
    }
}

#endif //RIGIDBODY_H
