#include "Engine/Core/God.h"

#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/Scripting/Prefab.h"

namespace Core
{
    UnorderedMap<String, UniquePtr<Prefab>> God::m_prefabs;
    UnorderedMap<GUID, UniquePtr<Entity>> God::m_entities;

    God::God()
    {
    }

    void God::SetupEmbedding(LState* L)
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

    void God::RegisterPrefab(LState* self, const String& name, LRef prefab)
    {
        UniquePtr<Prefab> prefabPtr = std::make_unique<Prefab>(self, name, prefab);
        m_prefabs.insert(std::make_pair(name, std::move(prefabPtr)));
    }

    GUID God::SpawnPrefab(LState* self, const String& name)
    {
        using namespace luabridge;

        Prefab& prefab = *m_prefabs[name];
        if (prefab.IsValid())
        {
            return prefab.CallFn();
        }
    }

    Prefab& God::GetPrefab(const String& name)
    {
        return *m_prefabs[name];
    }

    bool God::HasPrefab(const String& name)
    {
        return m_prefabs[name] != nullptr;
    }

    void God::ProcessAsset(LState* self, LRef asset)
    {
        String assetType = asset["type"].tostring();
        String assetPath = asset["file"].tostring();

        std::cout << "Asset Type: " << asset["type"].tostring() << std::endl;
        std::cout << "Asset Path: " << asset["file"].tostring() << std::endl;
    }
}
