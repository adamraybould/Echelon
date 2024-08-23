#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Utility/Commons.h"

namespace Core::Systems
{
    class EntityManager
    {
    private:
        Map<UInt64, UniquePtr<Entity>> m_entities;

    public:
        EntityManager();
        ~EntityManager();

        void Initialise();
        void Update(float delta);
        void Render(Renderer& renderer);

        /* Returns an Entity with the Specified ID */
        Entity* GetEntity(UInt64 ID);

        /* Returns an Entity with the Specified Name */
        Entity* GetEntity(const char* name);

        /* Returns an Entity at a Point in the World */
        Entity* GetEntityAtPoint(const Vector2& point);

        template<typename T, typename... Args>
        inline T& CreateEntity(Args&&... args)
        {
            // Ensures T is of type Entity
            static_assert(std::is_base_of_v<Entity, T>, "T must be a subclass of Entity");

            auto entity = std::make_unique<T>(std::forward<Args>(args)...);
            T& entityRef = *entity;

            m_entities.insert(std::make_pair(entity->GetID(), std::move(entity)));

            return entityRef;
        }
    };
}

#endif //ENTITYMANAGER_H
