#ifndef WORLD_H
#define WORLD_H
#include "Scripting/IBinder.h"

namespace Core
{
    namespace Scripting { class Prefab; }

    class Entity;

    using namespace Scripting;
    class World : public IBinder
    {
    public:
        World();

        static Entity& CreateEntity();
        static void RemoveEntity(Entity& entity);

        static GUID SpawnPrefab(const char* name);

        void SetupEmbedding(lua_State* L) override;
    };
}

#endif //WORLD_H
