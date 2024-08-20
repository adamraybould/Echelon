#ifndef COMPONENT_H
#define COMPONENT_H
#include "Utility/Commons.h"

class SDL_Renderer;

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

        virtual void Initialize() = 0;
        virtual void Update(float delta) = 0;
        virtual void Render(SDL_Renderer& renderer) = 0;
        virtual void Destroy() = 0;

        /* Returns the Owner of this Component */
        Entity& GetOwner() const { return m_rOwner; }

        /* Returns the Unique ID of this Component */
        UInt64 GetID() const { return m_ID; }

        void SetActive(bool active) { m_isActive = active; }
        bool IsActive() const { return m_isActive; }
    };
}

#endif //COMPONENT_H
