#include "Engine/Core/ECS/Components/Rigidbody.h"
#include <box2d/box2d.h>

#include "Engine/Core/Physics.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Utility/Constants.h"

namespace Core
{
    namespace Components
    {
        Rigidbody::Rigidbody(Entity& owner) : Component(owner)
        {
            m_pBody = Physics::CreateDynamicBody(GetOwner().GetTransform().GetWorldPosition(), 16, 32);
            m_pBody->SetEnabled(true);
        }

        Rigidbody::~Rigidbody()
        {
            if (m_pBody != nullptr)
            {
                Physics::DestroyBody(m_pBody);
            }
        }

        void Rigidbody::SetupEmbedding(lua_State* L)
        {
            Component::SetupEmbedding(L);

            BindClass<Rigidbody>(L);
            BindFunction<Rigidbody>(L, "SetLinearDamping", &Rigidbody::SetLinearDamping);
            BindFunction<Rigidbody>(L, "SetAngularDamping", &Rigidbody::SetAngularDamping);

            BindFunction<Rigidbody>(L, "ApplyForce", &Rigidbody::ApplyForce);
            BindFunction<Rigidbody>(L, "ApplyImpulse", &Rigidbody::ApplyImpulse);
        }

        void Rigidbody::Initialize()
        {
            Component::Initialize();
        }

        void Rigidbody::Update(float delta)
        {
            Component::Update(delta);

            m_pBody->SetLinearDamping(m_linearDamping);
            m_pBody->SetAngularDamping(m_angularDamping);

            Vector2 position = Vector2(m_pBody->GetPosition().x * PPM, m_pBody->GetPosition().y * PPM);
            float angle = m_pBody->GetAngle();

            GetOwner().GetTransform().SetWorldPosition(position);
            GetOwner().GetTransform().Rotation = angle * (180.0f / M_PI);
        }

        void Rigidbody::Render(Renderer& renderer)
        {
            Component::Render(renderer);
        }

        void Rigidbody::Destroy()
        {
            Component::Destroy();
        }

        void Rigidbody::ApplyForce(LRef force)
        {
            b2Vec2 vecForce = b2Vec2(force["x"], force["y"]);
            m_pBody->ApplyForceToCenter(vecForce, true);
        }

        void Rigidbody::ApplyImpulse(LRef force)
        {
            b2Vec2 vecForce = b2Vec2(force["x"], force["y"]);
            m_pBody->ApplyLinearImpulseToCenter(vecForce, true);
        }
    }
}
