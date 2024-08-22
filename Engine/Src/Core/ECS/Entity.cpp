#include "Engine/Core/ECS/Entity.h"
#include "Engine/Utility/Utility.h"

namespace Core
{
    Entity::Entity(const char* name)
    {
        m_ID = Utility::GenerateUniqueID();
        m_name = name;

        m_bounds = Rectangle();
        m_transform = &AddComponent<Transform>();
    }

    Entity::~Entity()
    {
        RemoveAllComponents();
    }

    void Entity::Update(float delta)
    {
        // Update Bounds
        Vector2 worldPosition = GetTransform().GetWorldPosition();
        m_bounds.X = GetTransform().Position.X;
        m_bounds.Y = GetTransform().Position.Y;

        for (UInt i = 0; i < m_components.size(); i++)
        {
            Component& component = *m_components[i];
            if (component.IsActive())
            {
                component.Update(delta);
            }
        }

        // Update Children
        Array<Transform*> children = m_transform->GetChildren();
        for (UInt i = 0; i < children.size(); i++)
        {
            children[i]->GetOwner().Update(delta);
        }
    }

    void Entity::Render(Renderer& renderer)
    {
        for (UInt i = 0; i < m_components.size(); i++)
        {
            Component& component = *m_components[i];
            if (component.IsActive())
            {
                component.Render(renderer);
            }
        }

        // Render Children
        Array<Transform*> children = m_transform->GetChildren();
        for (UInt i = 0; i < children.size(); i++)
        {
            children[i]->GetOwner().Render(renderer);
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
