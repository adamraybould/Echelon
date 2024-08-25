#ifndef LEVEL_H
#define LEVEL_H
#include "Engine/Utility/Commons.h"
#include "Engine/Core/Systems/EntityManager.h"

namespace Core
{
    class Renderer;

    using namespace Systems;
    namespace States
    {
        class Level
        {
        private:
            EntityManager& m_entityManager;

        public:
            Level(EntityManager& entityManager);
            virtual ~Level();

            virtual void Initialize() = 0;
            virtual void Update(float delta) = 0;
            virtual void Render(Renderer& renderer) = 0;

            template<typename T, typename... Args>
            inline T& Instantiate(const char* name, Transform& parent, Args... args)
            {
                T& entity = m_entityManager.CreateEntity<T>(name, std::forward<Args>(args)...);

                Entity& baseEntity = static_cast<Entity&>(entity);
                parent.AddChild(baseEntity.GetTransform());
                return entity;
            }

            template<typename T, typename... Args>
            inline T& Instantiate(const char* name, const Vector2 position = {0, 0}, const float rotation = 0.0f, const Vector2 scale = {1, 1}, Args... args)
            {
                T& entity = m_entityManager.CreateEntity<T>(name, std::forward<Args>(args)...);

                Entity& baseEntity = static_cast<Entity&>(entity);
                baseEntity.GetTransform().SetWorldPosition(position);
                baseEntity.GetTransform().SetWorldRotation(rotation);
                baseEntity.GetTransform().SetWorldScale(scale);

                return entity;
            }

            template<typename T, typename... Args>
            inline T& Instantiate(const char* name, const Vector2 position, const float rotation, Transform& parent, Args... args)
            {
                T& entity = m_entityManager.CreateEntity<T>(name, std::forward<Args>(args)...);

                Entity& baseEntity = static_cast<Entity&>(entity);
                baseEntity.GetTransform().SetWorldPosition(position);
                baseEntity.GetTransform().SetWorldRotation(rotation);

                parent.AddChild(baseEntity.GetTransform());
                return entity;
            }
        };
    }
}

#endif //LEVEL_H
