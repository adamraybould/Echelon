#ifndef GOD_H
#define GOD_H
#include "Core/Scripting/IBinder.h"
#include "Systems/StateSystem.h"

namespace Core
{
    namespace Scripting { class Prefab; }
    class Entity;

    using namespace Scripting;
    using namespace Systems;
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
        static GUID SpawnPrefab(LState* self, String name);
        static bool HasPrefab(const String& name);
        static Prefab& GetPrefab(const String& name);

        // -- Camera
        static void SetCameraPosition(LState* L, const LRef& position);
    };
}

#endif //GOD_H
