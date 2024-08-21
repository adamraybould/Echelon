#include "Systems/EntityManager.h"

#include "Rendering/Renderer.h"

namespace Engine::Systems
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

    void EntityManager::InitializeEntities()
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); ++i)
        {
            i->second->Initialize();
        }
    }

    void EntityManager::UpdateEntities(float delta)
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

    void EntityManager::RenderEntities(Renderer& renderer)
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

    Entity* EntityManager::GetEntity(UInt64 ID)
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
}
