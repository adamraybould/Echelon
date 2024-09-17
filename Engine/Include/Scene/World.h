#ifndef WORLD_H
#define WORLD_H
#include "Core/Scripting/IBinder.h"

namespace Core::Scripting { class Prefab; }

namespace Scene
{
    class Entity;

    class World final : IBinder
    {
    private:
        static UnorderedMap<String, UniquePtr<Scripting::Prefab>> m_prefabs; // List of Registered Prefabs
        static UnorderedMap<GUID, UniquePtr<Entity>> m_entities; // List of Created Entities

    public:
        World();
        ~World() override;

        void Initialise() const;
        void Update(float delta) const;

        void SetupEmbedding(lua_State* L) override;

        static void RegisterPrefab(LState* L, const String& name, LRef prefab); /* Registers and Stores a Prefab for later use */
        static GUID SpawnPrefab(LState* L, const String& name); /* Spawns a Prefab defined in Lua. Returns the Entities/Prefabs GUID */

        static Entity& CreateEntity(); /* Creates a Base Entity with a unique GUID */
        static Entity* FindEntity(int x, int y); /* Returns an Entity at X and Y */

        static Entity* GetEntityByGUID(const GUID& guid); /* Returns a Entity with the specified GUID */

        /* Returns an array of Entities within a Radius around X and Y */
        //Array<Entity&> FindEntities(int x, int y, float radius);
    };
}

#endif //WORLD_H
