#include "Engine/Core/Physics.h"

#include "Engine/Utility/Constants.h"
#include "Engine/Utility/DebugDraw.h"

namespace Core
{
    UniquePtr<b2World> Physics::m_pWorld;
    UniquePtr<DebugDraw> Physics::m_pDebugDraw;

    Physics::Physics(Renderer& renderer)
    {
        m_pWorld = std::make_unique<b2World>(b2Vec2(0.0f, 0.0f));

        m_pDebugDraw = std::make_unique<DebugDraw>(renderer);
        m_pWorld->SetDebugDraw(m_pDebugDraw.get());

        uint32_t flags = b2Draw::e_shapeBit;
        m_pDebugDraw->SetFlags(flags);
    }

    Physics::~Physics()
    {
        m_pWorld.reset();
        m_pDebugDraw.reset();
    }

    void Physics::Update() const
    {
        m_pWorld->Step(1.0f / 60.0f, 6, 2);
    }

    void Physics::Render(Renderer& renderer)
    {
        //m_pDebugDraw->DrawBox2DCollision(m_pWorld.get());
        //m_pWorld->DebugDraw();
    }

    b2Body* Physics::CreateDynamicBody(const Vector2F position, const UInt width, const UInt height)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = b2Vec2(position.X / PPM, position.Y / PPM);
        bodyDef.fixedRotation = true;

        b2Body* body = m_pWorld->CreateBody(&bodyDef);

        b2PolygonShape boxCollider;
        boxCollider.SetAsBox((width / PPM), (height / PPM));

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxCollider;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution = 0.0f;
        body->CreateFixture(&fixtureDef);

        return body;
    }

    b2Body* Physics::CreateStaticBody(const Vector2F position, const UInt width, const UInt height)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position = b2Vec2(position.X / PPM, position.Y / PPM);
        bodyDef.fixedRotation = true;

        b2Body* body = m_pWorld->CreateBody(&bodyDef);

        b2PolygonShape boxCollider;
        boxCollider.SetAsBox(width / PPM, height / PPM);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxCollider;
        body->CreateFixture(&fixtureDef);

        return body;
    }

    void Physics::DestroyBody(b2Body* body)
    {
        m_pWorld->DestroyBody(body);
    }
}
