#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "Component.h"

class b2Body;

namespace Core
{
    namespace Components
    {
        class Rigidbody : public Component
        {
        private:
            b2Body* m_pBody = nullptr;

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

            void SetLinearDamping(float value) { m_linearDamping = value; }
            void SetAngularDamping(float value) { m_angularDamping = value; }

            void ApplyForce(LRef force);
            void ApplyImpulse(LRef force);
        };
    }
}

#endif //RIGIDBODY_H
