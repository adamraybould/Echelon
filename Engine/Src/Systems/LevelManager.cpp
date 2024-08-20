#include "Systems/LevelManager.h"

namespace Engine::Systems
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

    void LevelManager::Update(float delta)
    {
        if (m_currentLevel != nullptr)
        {
            m_currentLevel->Update(delta);
        }
    }

    void LevelManager::Render(SDL_Renderer& renderer)
    {
        if (m_currentLevel != nullptr)
        {
            m_currentLevel->Render(renderer);
        }
    }
}
