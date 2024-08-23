#include "Engine/Core/Systems/EntityManager.h"
#include "Engine/Core/Renderer.h"

namespace Core::Systems
{
    EntityManager::EntityManager()
    {
    }

    EntityManager::~EntityManager()
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); i++)
        {
            i->second.reset();
        }

        m_entities.clear();
    }

    void EntityManager::Initialise()
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); ++i)
        {
            i->second->Initialize();
        }
    }

    void EntityManager::Update(const float delta)
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); ++i)
        {
            Entity& entity = *i->second;
            if (!entity.GetTransform().HasParent())
            {
                entity.Update(delta);
            }
        }
    }

    void EntityManager::Render(Renderer& renderer)
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); ++i)
        {
            Entity& entity = *i->second;
            if (!entity.GetTransform().HasParent())
            {
                entity.Render(renderer);
            }
        }
    }

    Entity* EntityManager::GetEntity(const UInt64 ID)
    {
        Map<UInt64, UniquePtr<Entity>>::iterator i = m_entities.find(ID);
        if (i != m_entities.end())
        {
            return i->second.get();
        }
        else
        {
            return nullptr;
        }
    }

    Entity* EntityManager::GetEntity(const char* name)
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); ++i)
        {
            if (i->second->GetName() == name)
                return i->second.get();
        }

        return nullptr;
    }

    Entity* EntityManager::GetEntityAtPoint(const Vector2& point)
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); ++i)
        {
            Entity& entity = *i->second;
            Rectangle bounds = entity.GetBounds();

            if (bounds.IsZero())
                continue;

            if (bounds.ContainsPoint(point))
                return &entity;
        }

        // No Entity could be Found
        return nullptr;
    }
}
