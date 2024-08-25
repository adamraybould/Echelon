#include "Engine/Core/God.h"

#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/Scripting/Prefab.h"

namespace Core
{
    Array<const char*> God::m_registeredPrefabs;
    UnorderedMap<GUID, UniquePtr<Entity>> God::m_entities;

    God::God()
    {
    }

    void God::SetupEmbedding(lua_State* L)
    {
        BindStaticFunction(L, "God", "RegisterPrefab", &God::RegisterPrefab);
        BindStaticFunction(L, "God", "SpawnPrefab", &God::SpawnPrefab);
        BindStaticFunction(L, "God", "CreateEntity", &God::CreateEntity);
    }

    Entity& God::CreateEntity()
    {
        UniquePtr<Entity> entity = std::make_unique<Entity>("");
        GUID guid = entity->GetGUID();

        m_entities.insert(std::make_pair(guid, std::move(entity)));
        return *m_entities[guid];
    }

    void God::RegisterPrefab(lua_State* self, const char* name)
    {
        m_registeredPrefabs.push_back(name);
    }

    GUID God::SpawnPrefab(lua_State* self, const char* name)
    {
        using namespace luabridge;
        LuaRef prefabRef = getGlobal(self, "Prefabs")[name];
        if (!prefabRef["fn"].isFunction())
        {
            std::cerr << "Error: No fn() function found for Prefab '" << name << "'" << std::endl;
            return "ERR";
        }

        SharedPtr<Prefab> prefab = std::make_shared<Prefab>(self, name, prefabRef["fn"]);
        return prefab.get()->CallFn();
    }
}
