#include "Engine/Core/World.h"

#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/Scripting/Prefab.h"
#include "Engine/Utility/Utility.h"

namespace Core
{
    World::World()
    {

    }

    Entity& World::CreateEntity()
    {
        return *std::make_unique<Entity>("");
    }

    void World::RemoveEntity(Entity& entity)
    {
    }

    GUID World::SpawnPrefab(const char* name)
    {
        return Utility::GenerateGUID();
    }

    void World::SetupEmbedding(lua_State* L)
    {
        BindStaticFunction(L, "World", "CreateEntity", &World::CreateEntity);
        BindStaticFunction(L, "World", "SpawnPrefab", &World::SpawnPrefab);
    }
}
