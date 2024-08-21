#include "Engine/Systems/LevelManager.h"

namespace Core::Systems
{
    LevelManager* LevelManager::m_pInstance;

    LevelManager::LevelManager()
    {
        m_pInstance = this;
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

    void LevelManager::Initialize() const
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
