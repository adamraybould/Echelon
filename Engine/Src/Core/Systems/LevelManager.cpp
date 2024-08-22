#include "Engine/Core/Systems/LevelManager.h"

namespace Core::Systems
{
    LevelManager::LevelManager(EntityManager& entityManager) : m_entityManager(entityManager)
    {
        m_currentLevel = nullptr;
    }

    LevelManager::~LevelManager()
    {
        for (UInt i = 0; i < m_levels.size(); i++)
        {
            m_levels[i].reset();
        }

        m_levels.clear();
    }

    void LevelManager::Initialise() const
    {
        for (UInt i = 0; i < m_levels.size(); i++)
        {
            m_levels[i]->Initialize();
        }
    }

    void LevelManager::Update(float delta) const
    {
        if (m_currentLevel != nullptr)
        {
            m_currentLevel->Update(delta);
        }
    }

    void LevelManager::Render(Renderer& renderer) const
    {
        if (m_currentLevel != nullptr)
        {
            m_currentLevel->Render(renderer);
        }
    }
}
