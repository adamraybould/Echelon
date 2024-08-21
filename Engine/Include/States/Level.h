#ifndef LEVEL_H
#define LEVEL_H
#include "Utility/Commons.h"
#include "Systems/EntityManager.h"

namespace Engine::Rendering
{
    class Renderer;
}

using namespace Engine::Rendering;
namespace Engine::States
{
    class Level
    {
    private:
        UInt64 m_ID;
        UniquePtr<Systems::EntityManager> m_pEntityManager;

    public:
        Level();
        virtual ~Level();

        virtual void Initialize();
        virtual void Update(float delta);
        virtual void Render(Renderer& renderer);

        UInt64 GetID() const { return m_ID; }
        Systems::EntityManager& GetEntityManager() const { return *m_pEntityManager; }

        template<typename T, typename... Args>
        inline T& Instantiate(Transform& parent, Args... args)
        {
            T& entity = GetEntityManager().CreateEntity<T>(std::forward<Args>(args)...);

            Entity& baseEntity = static_cast<Entity&>(entity);
            parent.AddChild(baseEntity.GetTransform());
            return entity;
        }

        template<typename T, typename... Args>
        inline T& Instantiate(const Vector2 position = {0, 0}, const float rotation = 0.0f, const Vector2 scale = {1, 1}, Args... args)
        {
            T& entity = GetEntityManager().CreateEntity<T>(std::forward<Args>(args)...);

            Entity& baseEntity = static_cast<Entity&>(entity);
            baseEntity.GetTransform().SetWorldPosition(position);
            baseEntity.GetTransform().SetWorldRotation(rotation);
            baseEntity.GetTransform().SetWorldScale(scale);

            return entity;
        }

        template<typename T, typename... Args>
        inline T& Instantiate(const Vector2 position, const float rotation, Transform& parent, Args... args)
        {
            T& entity = GetEntityManager().CreateEntity<T>(std::forward<Args>(args)...);

            Entity& baseEntity = static_cast<Entity&>(entity);
            baseEntity.GetTransform().SetWorldPosition(position);
            baseEntity.GetTransform().SetWorldRotation(rotation);

            parent.AddChild(baseEntity.GetTransform());
            return entity;
        }
    };
}

#endif //LEVEL_H
