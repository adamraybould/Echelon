#include "Scene/Entities/Components/Component.h"

#include "Core/Utility.h"
#include "Scene/Entities/Entity.h"
#include "Core/Scripting/Prefab.h"

namespace Core::Components
{
    Component::Component(Entity& owner) : m_owner(owner), m_isActive(true)
    {
        m_guid = Utility::GenerateGUID();
    }

    void Component::SetupEmbedding(lua_State* L)
    {
        using namespace luabridge;
        BindClass<Component>(L);
        getGlobalNamespace(L).beginClass<Component>("Component").addConstructor<void (*)(Entity&)>().endClass();
    }

    PrefabAsset* Component::GetPrefabAsset(const AssetType type) const
    {
        if (m_owner.HasPrefab())
        {
            Prefab& prefab = m_owner.GetPrefab();
            PrefabAsset* asset = prefab.GetAsset(type);
            if (asset != nullptr)
                return asset;
        }

        // No Prefab Found
        return nullptr;
    }
}
