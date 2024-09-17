#include "Core/Scripting/Engine.h"
#include "Core/Camera.h"
#include "Scene/Entities/Entity.h"
#include "tmxlite/Map.hpp"

#include "Systems/EntityManager.h"
#include "Core/Scripting/Prefab.h"

using namespace Scene;
namespace Core
{
    using namespace Scripting;
    using namespace Systems;

    UnorderedMap<String, UniquePtr<Prefab>> Engine::m_prefabs;
    UnorderedMap<GUID, UniquePtr<Entity>> Engine::m_entities;

    Engine::Engine()
    {
    }

    void Engine::SetupEmbedding(LState* L)
    {
        BindStaticFunction(L, "Engine", "SetCameraPosition", &Engine::SetCameraPosition);
    }

    Prefab& Engine::GetPrefab(const String& name)
    {
        return *m_prefabs[name];
    }

    bool Engine::HasPrefab(const String& name)
    {
        return m_prefabs[name] != nullptr;
    }

    void Engine::SetCameraPosition(LState* L, const LRef& position)
    {
        Camera::Main->GetTransform().SetWorldPosition(Vector2F(position["x"], position["y"]));
    }
}
