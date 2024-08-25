#ifndef COMPONENT_H
#define COMPONENT_H
#include "Engine/Core/Scripting/IBinder.h"
#include "Engine/Utility/Commons.h"

namespace Core
{
    class Entity;
    class Renderer;

    namespace Components
    {
        using namespace Core;
        class Component : public IBinder
        {
        private:
            Entity& m_rOwner;
            GUID m_guid;

            bool m_isActive;

        public:
            explicit Component(Entity& owner);
            virtual ~Component() = default;

            virtual void Initialize() {}
            virtual void Update(float delta) {}
            virtual void Render(Renderer& renderer) {}
            virtual void Destroy() {}

            /* Returns the Owner of this Component */
            Entity& GetOwner() const { return m_rOwner; }

            /* Returns the Unique GUID of this Component */
            GUID GetGUID() const { return m_guid; }

            void SetActive(bool active) { m_isActive = active; }
            bool IsActive() const { return m_isActive; }

            void SetupEmbedding(lua_State* L) override;
        };
    }
}

using namespace Core::Components;
#endif //COMPONENT_H
