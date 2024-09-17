#include "Scene/World.h"

#include "Core/Scripting/Prefab.h"
#include "Scene/Entities/Entity.h"
#include "Systems/EntityManager.h"

namespace Scene
{
    UnorderedMap<String, UniquePtr<Prefab>> World::m_prefabs;
    UnorderedMap<GUID, UniquePtr<Entity>> World::m_entities;

    World::World()
    {
    }

    World::~World()
    {
        for (auto& entity : m_entities)
        {
            entity.second.reset();
        }
        m_entities.clear();
    }

    void World::Initialise() const
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); ++i)
        {
            i->second->Initialize();
        }
    }

    void World::Update(const float delta) const
    {
        for (auto& entity : m_entities)
        {
            entity.second->Update(delta);
        }
    }

    void World::SetupEmbedding(lua_State* L)
    {
        BindStaticFunction(L, "World", "RegisterPrefab", &World::RegisterPrefab);
        BindStaticFunction(L, "World", "SpawnPrefab", &World::SpawnPrefab);

        BindStaticFunction(L, "World", "CreateEntity", &World::CreateEntity);
        BindStaticFunction(L, "World", "FindEntity", &World::FindEntity);

        BindStaticFunction(L, "World", "GetEntityByGUID", &World::GetEntityByGUID);

        //BindFunction<World>(L, "FindEntities", &World::FindEntities);
    }

    void World::RegisterPrefab(LState* L, const String& name, LRef prefab)
    {
        UniquePtr<Prefab> prefabPtr = std::make_unique<Prefab>(L, name, prefab);
        m_prefabs.insert(std::make_pair(name, std::move(prefabPtr)));
    }

    Core::GUID World::SpawnPrefab(LState* L, const String& name)
    {
        Prefab& prefab = *m_prefabs[name];
        if (prefab.IsValid())
        {
            GUID entity = prefab.CallFn();
            Systems::EntityManager::GetEntityByGUID(entity)->SetName(name);

            return entity;
        }

        return "GUID ERROR";
    }

    Entity& World::CreateEntity()
    {
        auto entity = std::make_unique<Entity>("");
        GUID guid = entity->GetGUID();

        m_entities.insert(std::make_pair(guid, std::move(entity)));
        return *m_entities[guid];
    }

    Entity* World::FindEntity(int x, int y)
    {
        for (auto& entityList : m_entities)
        {
            Entity& entity = *entityList.second;
        }

        return nullptr;
    }

    Entity* World::GetEntityByGUID(const Core::GUID& guid)
    {
        if (m_entities.contains(guid))
            return m_entities[guid].get();

        std::cerr << "Entity with GUID '" << guid << "' Can't be Found" << std::endl;
        return nullptr;
    }
}
