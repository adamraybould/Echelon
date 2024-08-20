#include "ECS/Entity.h"
#include "Utility/Utility.h"

namespace Engine::ECS
{
    Entity::Entity()
    {
        m_ID = Utility::GenerateUniqueID();
    }

    Entity::~Entity()
    {
        RemoveAllComponents();
    }

    void Entity::Update(float delta)
    {
        for(UInt i = 0; i < m_components.size(); i++)
        {
            Component& component = *m_components[i];
            if (component.IsActive())
            {
                component.Update(delta);
            }
        }
    }

    void Entity::Render(SDL_Renderer& renderer)
    {
        for(UInt i = 0; i < m_components.size(); i++)
        {
            Component& component = *m_components[i];
            if (component.IsActive())
            {
                component.Render(renderer);
            }
        }
    }

    void Entity::RemoveAllComponents()
    {
        for(UInt i = 0; i < m_components.size(); i++)
        {
            m_components[i].reset();
        }

        m_components.clear();
    }
}
