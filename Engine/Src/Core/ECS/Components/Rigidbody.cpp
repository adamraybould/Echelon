#include "Engine/Core/ECS/Components/Rigidbody.h"
#include <box2d/box2d.h>

#include "Engine/Core/Physics.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/ECS/Components/SpriteRenderer.h"
#include "Engine/Utility/Constants.h"

namespace Core
{
    namespace Components
    {
        Rigidbody::Rigidbody(Entity& owner) : Component(owner)
        {
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
            BindFunction<Rigidbody>(L, "CreateStaticBody", &Rigidbody::CreateStaticBody);
            BindFunction<Rigidbody>(L, "CreateDynamicBody", &Rigidbody::CreateDynamicBody);

            BindFunction<Rigidbody>(L, "SetLinearDamping", &Rigidbody::SetLinearDamping);
            BindFunction<Rigidbody>(L, "SetAngularDamping", &Rigidbody::SetAngularDamping);

            BindFunction<Rigidbody>(L, "ApplyForce", &Rigidbody::ApplyForce);
            BindFunction<Rigidbody>(L, "ApplyImpulse", &Rigidbody::ApplyImpulse);

            BindFunction<Rigidbody>(L, "SetPosition", &Rigidbody::SetPositionL);
        }

        void Rigidbody::Initialize()
        {
            CreateBody();
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

        void Rigidbody::CreateStaticBody()
        {
            m_bodyType = BodyType::STATIC;
        }

        void Rigidbody::CreateDynamicBody()
        {
            m_bodyType = BodyType::DYNAMIC;
        }

        void Rigidbody::ApplyForce(const LRef& force) const
        {
            b2Vec2 vecForce = b2Vec2(force["x"], force["y"]);
            m_pBody->ApplyForceToCenter(vecForce, true);
        }

        void Rigidbody::ApplyImpulse(const LRef& force) const
        {
            b2Vec2 vecForce = b2Vec2(force["x"], force["y"]);
            m_pBody->ApplyLinearImpulseToCenter(vecForce, true);
        }

        void Rigidbody::SetPosition(const Vector2& position) const
        {
            b2Vec2 pos = b2Vec2(position.X / PPM, position.Y / PPM);
            m_pBody->SetTransform(pos, m_pBody->GetAngle());
        }

        void Rigidbody::SetPositionL(const LRef& position) const
        {
            int x = position["x"];
            int y = position["y"];

            b2Vec2 pos = b2Vec2(x / PPM, y / PPM);
            m_pBody->SetTransform(pos, m_pBody->GetAngle());
        }

        void Rigidbody::CreateBody()
        {
            Vector2 collisionSize = GetSpriteSize();

            if (m_bodyType == BodyType::STATIC)
            {
                m_pBody = Physics::CreateStaticBody(GetOwner().GetTransform().GetWorldPosition(), collisionSize.X, collisionSize.Y);
                m_pBody->SetEnabled(true);
            }
            else if (m_bodyType == BodyType::DYNAMIC)
            {
                m_pBody = Physics::CreateDynamicBody(GetOwner().GetTransform().GetWorldPosition(), collisionSize.X, collisionSize.Y);
                m_pBody->SetEnabled(true);
            }
        }

        Vector2 Rigidbody::GetSpriteSize() const
        {
            SpriteRenderer* renderer = GetOwner().GetComponent<SpriteRenderer>();
            if (renderer != nullptr)
            {
                SpriteSheet* spriteSheet = static_cast<SpriteSheet*>(&renderer->GetSprite());
                if (spriteSheet != nullptr)
                {
                    return Vector2(spriteSheet->GetFrameWidth() * 0.5f, spriteSheet->GetFrameHeight() * 0.5f);
                }
            }

            return Vector2(16, 16);
        }
    }
}
