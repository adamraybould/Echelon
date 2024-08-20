#include "States/GameState.h"
#include "Systems/LevelManager.h"

namespace Engine::States
{
    GameState::GameState()
    {
        m_pLevelManager = std::make_unique<Systems::LevelManager>();
    }

    GameState::~GameState()
    {
        m_pLevelManager.reset();
    }

    void GameState::Initialize()
    {
        if (m_pLevelManager != nullptr)
        {
            m_pLevelManager->Initialize();
        }
    }

    void GameState::Update(float delta)
    {
        if (m_pLevelManager != nullptr)
        {
            m_pLevelManager->Update(delta);
        }
    }

    void GameState::Render(SDL_Renderer& renderer)
    {
        if (m_pLevelManager != nullptr)
        {
            m_pLevelManager->Render(renderer);
        }
    }
}
