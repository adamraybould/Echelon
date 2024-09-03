#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Utility/Commons.h"

namespace Core::Systems
{
    class EntityManager
    {
    private:
        static UnorderedMap<GUID, UniquePtr<Entity>> m_entities;
        static bool m_isInitialised;

    public:
        EntityManager();
        ~EntityManager();

        void Initialise();
        void Update(float delta);

        static Entity& CreateEntity();

        /* Returns an Entity with the Specified ID */
        static Entity* GetEntityByGUID(GUID guid);

        /* Returns an Entity with the Specified Name */
        static Entity* GetEntityByName(const char* name);

        /* Returns an Entity at a Point in the World */
        static Entity* GetEntityAtPoint(const Vector2& point);
    };
}

#endif //ENTITYMANAGER_H
