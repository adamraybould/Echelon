#include "Systems/EntityManager.h"

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
            i->second->Update(delta);
        }
    }

    void EntityManager::RenderEntities(SDL_Renderer& renderer)
    {
        for (auto i = m_entities.begin(); i != m_entities.end(); ++i)
        {
            i->second->Render(renderer);
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
