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
        static UnorderedMap<String, UniquePtr<Prefab>> m_prefabs;
        static UnorderedMap<GUID, UniquePtr<Entity>> m_entities;

    public:
        God();
        void SetupEmbedding(LState* L) override;

        static Entity& CreateEntity();

        static void RegisterPrefab(LState* self, const String& name, LRef prefab);
        static GUID SpawnPrefab(LState* self, const String& name);

        static Prefab& GetPrefab(const String& name);
        static bool HasPrefab(const String& name);

        static UnorderedMap<GUID, UniquePtr<Entity>>& GetEntities() { return m_entities; }
    private:
        static void ProcessAsset(LState* self, LRef asset);
    };
}

#endif //GOD_H
