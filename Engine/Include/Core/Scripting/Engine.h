#ifndef GOD_H
#define GOD_H
#include "Core/Scripting/IBinder.h"
#include "Systems/StateSystem.h"

namespace Scene { class Entity; }

namespace Core
{
    namespace Scripting { class Prefab; }

    class Engine : IBinder
    {
    private:
        static UnorderedMap<String, UniquePtr<Scripting::Prefab>> m_prefabs;
        static UnorderedMap<GUID, UniquePtr<Scene::Entity>> m_entities;

    public:
        Engine();
        void SetupEmbedding(LState* L) override;

        // -- Prefabs
        static bool HasPrefab(const String& name);
        static Scripting::Prefab& GetPrefab(const String& name);

        // -- Camera
        static void SetCameraPosition(LState* L, const LRef& position);
    };
}

#endif //GOD_H
