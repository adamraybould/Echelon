#ifndef GOD_H
#define GOD_H
#include "Scripting/IBinder.h"
#include "Engine/Utility/Commons.h"

namespace Core
{
    namespace Scripting { class Prefab; }
    class Entity;

    using namespace Scripting;
    class God : IBinder
    {
    private:
        static Array<const char*> m_registeredPrefabs;
        static UnorderedMap<GUID, UniquePtr<Entity>> m_entities;

    public:
        God();
        void SetupEmbedding(lua_State* L) override;

        static Entity& CreateEntity();
        static void RegisterPrefab(lua_State* self, const char* name);

        static GUID SpawnPrefab(lua_State* self, const char* name);
    };
}

#endif //GOD_H
