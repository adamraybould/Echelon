#ifndef GOD_H
#define GOD_H
#include "Scripting/IBinder.h"
#include "Engine/Utility/Commons.h"

namespace Core
{
    namespace Scripting { class Prefab; }
    class Entity;

    using namespace Scripting;
    class Engine : IBinder
    {
    private:
        static UnorderedMap<String, UniquePtr<Prefab>> m_prefabs;
        static UnorderedMap<GUID, UniquePtr<Entity>> m_entities;

    public:
        Engine();
        void SetupEmbedding(LState* L) override;

        static Entity& CreateEntity();

        // -- Prefabs
        static void RegisterPrefab(LState* self, const String& name, LRef prefab);
        static GUID SpawnPrefab(LState* self, const String& name);
        static bool HasPrefab(const String& name);
        static Prefab& GetPrefab(const String& name);

        // -- Camera
        static void SetCameraPosition(LState* L, LRef position);

        static UnorderedMap<GUID, UniquePtr<Entity>>& GetEntities() { return m_entities; }
    };
}

#endif //GOD_H
