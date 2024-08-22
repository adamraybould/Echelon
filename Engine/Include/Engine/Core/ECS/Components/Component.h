#ifndef COMPONENT_H
#define COMPONENT_H
#include "Engine/Utility/Commons.h"

namespace Core
{
    class Entity;
    class Renderer;

    namespace Components
    {
        using namespace Core;
        class Component
        {
        private:
            Entity& m_rOwner;
            UInt64 m_ID;

            bool m_isActive{};

        public:
            explicit Component(Entity& owner);
            virtual ~Component() = default;

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
}

using namespace Core::Components;
#endif //COMPONENT_H
