#include "Engine/Core/Systems/EntityManager.h"

#include "Engine/Core/Engine.h"
#include "Engine/Core/Renderer.h"

namespace Core::Systems
{
    UnorderedMap<GUID, UniquePtr<Entity>> EntityManager::m_entities;
    bool EntityManager::m_isInitialised = false;

    EntityManager::EntityManager()
    {
    }

    EntityManager::~EntityManager()
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); ++i)
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

        m_isInitialised = true;
    }

    void EntityManager::Update(const float delta)
    {
        for (auto& entity : m_entities)
        {
            entity.second->Update(delta);
        }
    }

    Entity& EntityManager::CreateEntity()
    {
        auto entity = std::make_unique<Entity>("");
        GUID guid = entity->GetGUID();

        m_entities.insert(std::make_pair(guid, std::move(entity)));
        return *m_entities[guid];
    }

    Entity* EntityManager::GetEntityByGUID(const GUID& guid)
    {
        if (m_entities.contains(guid))
            return m_entities[guid].get();

        return nullptr;
    }

    Entity* EntityManager::GetEntityByName(const String& name)
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); ++i)
        {
            if (i->second->GetName() == name)
                return i->second.get();
        }

        return nullptr;
    }

    Entity* EntityManager::GetEntityAtPoint(const Vector2F& point)
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
