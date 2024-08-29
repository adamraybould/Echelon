#include "Engine/Core/Engine.h"

#include "Engine/Core/Camera.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/Scripting/Prefab.h"
#include <tmxlite/Map.hpp>

namespace Core
{
    UnorderedMap<String, UniquePtr<Prefab>> Engine::m_prefabs;
    UnorderedMap<GUID, UniquePtr<Entity>> Engine::m_entities;

    Engine::Engine()
    {
    }

    void Engine::SetupEmbedding(LState* L)
    {
        BindStaticFunction(L, "Engine", "RegisterPrefab", &Engine::RegisterPrefab);
        BindStaticFunction(L, "Engine", "SpawnPrefab", &Engine::SpawnPrefab);
        BindStaticFunction(L, "Engine", "CreateEntity", &Engine::CreateEntity);

        BindStaticFunction(L, "Engine", "SetCameraPosition", &Engine::SetCameraPosition);
    }

    Entity& Engine::CreateEntity()
    {
        UniquePtr<Entity> entity = std::make_unique<Entity>("");
        GUID guid = entity->GetGUID();

        m_entities.insert(std::make_pair(guid, std::move(entity)));
        return *m_entities[guid];
    }

    void Engine::RegisterPrefab(LState* self, const String& name, LRef prefab)
    {
        UniquePtr<Prefab> prefabPtr = std::make_unique<Prefab>(self, name, prefab);
        m_prefabs.insert(std::make_pair(name, std::move(prefabPtr)));
    }

    GUID Engine::SpawnPrefab(LState* self, const String& name)
    {
        using namespace luabridge;

        Prefab& prefab = *m_prefabs[name];
        if (prefab.IsValid())
        {
            return prefab.CallFn();
        }

        return "GUID ERROR";
    }

    Prefab& Engine::GetPrefab(const String& name)
    {
        return *m_prefabs[name];
    }

    bool Engine::HasPrefab(const String& name)
    {
        return m_prefabs[name] != nullptr;
    }

    void Engine::SetCameraPosition(LState* L, LRef position)
    {
        Camera::Main->GetTransform().SetWorldPosition(Vector2(position["x"], position["y"]));
    }
}
