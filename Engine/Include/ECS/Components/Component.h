#ifndef COMPONENT_H
#define COMPONENT_H
#include "Utility/Commons.h"

namespace Engine::Rendering
{
    class Renderer;
}

using namespace Engine::Rendering;
namespace Engine::ECS
{
    class Entity;

    class Component
    {
    private:
        Entity& m_rOwner;
        UInt64 m_ID;

        bool m_isActive{};

    public:
        Component(Entity& owner);

        virtual void Initialize() {}
        virtual void Update(float delta) {}
        virtual void Render(Renderer& renderer) {}
        virtual void Destroy() {}

        /* Returns the Owner of this Component */
        Entity& GetOwner() const { return m_rOwner; }

        /* Returns the Unique ID of this Component */
        UInt64 GetID() const { return m_ID; }

        void SetActive(bool active) { m_isActive = active; }
        bool IsActive() const { return m_isActive; }
    };
}

#endif //COMPONENT_H
