#ifndef COMPONENT_H
#define COMPONENT_H
#include "Core/Scripting/IBinder.h"

namespace Core { class Renderer; }
namespace Core::Scripting { struct PrefabAsset; enum class AssetType; }

namespace Scene
{
    using GUID = Core::GUID;
    class Entity;

    namespace Components
    {
        using namespace Core;
        class Component : public IBinder
        {
        private:
            Entity& m_owner;
            GUID m_guid;

            bool m_isActive;

        public:
            explicit Component(Entity& owner);
            virtual ~Component() = default;

            void SetupEmbedding(lua_State* L) override;

            virtual void Initialize() {}
            virtual void Update(float delta) {}
            virtual void Render(Renderer& renderer) {}
            virtual void Destroy() {}

            /* Returns the Owner of this Component */
            Entity& GetOwner() const { return m_owner; }

            /* Returns the Unique GUID of this Component */
            GUID GetGUID() const { return m_guid; }

            void SetActive(bool active) { m_isActive = active; }
            bool IsActive() const { return m_isActive; }

        protected:
            Scripting::PrefabAsset* GetPrefabAsset(Scripting::AssetType type) const;
        };
    }
}

#endif //COMPONENT_H
