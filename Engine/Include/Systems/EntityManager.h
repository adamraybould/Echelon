#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "ECS/Entity.h"
#include "Utility/Commons.h"

using namespace Engine::ECS;
using namespace Engine::Rendering;
namespace Engine::Systems
{
    class EntityManager
    {
    private:
        Map<UInt64, UniquePtr<Entity>> m_entities;

    public:
        EntityManager();
        ~EntityManager();

        void InitializeEntities();
        void UpdateEntities(float delta);
        void RenderEntities(Renderer& renderer);

        /* Returns an Entity with the Specified ID */
        Entity* GetEntity(UInt64 ID);

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
