#include "Engine/Core/Systems/EntityManager.h"

#include "Engine/Core/God.h"
#include "Engine/Core/Renderer.h"

namespace Core::Systems
{
    EntityManager::EntityManager()
    {
        UnorderedMap<GUID, UniquePtr<Entity>>& scriptEntities = God::GetEntities();
        for (auto it = God::GetEntities().begin(); it != God::GetEntities().end(); ++it)
        {
            m_entities.insert(std::make_pair(it->first, std::move(it->second)));
        }
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

    Entity* EntityManager::GetEntityByGUID(GUID guid)
    {
        Map<GUID, UniquePtr<Entity>>::iterator i = m_entities.find(guid);
        if (i != m_entities.end())
        {
            return i->second.get();
        }
        else
        {
            return nullptr;
        }
    }

    Entity* EntityManager::GetEntityByName(const char* name)
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
