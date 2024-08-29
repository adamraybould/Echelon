#include "Engine/States/GameState.h"
#include "Engine/Core/Systems/LevelManager.h"
#include "Engine/Graphics/TileMap.h"

namespace Core::States
{
    GameState::GameState()
    {
        m_pEntityManager = std::make_unique<EntityManager>();
        m_pLevelManager = std::make_unique<LevelManager>(*m_pEntityManager);

        m_pTileMap = std::make_unique<TileMap>();
    }

    GameState::~GameState()
    {
        m_pEntityManager.reset();
        m_pLevelManager.reset();
    }

    void GameState::Initialize()
    {
        if (m_pEntityManager != nullptr)
            m_pEntityManager->Initialise();

        if (m_pLevelManager != nullptr)
            m_pLevelManager->Initialise();

        m_pTileMap->LoadTileMap("TestMap");
    }

    void GameState::Update(float delta)
    {
        if (m_pEntityManager != nullptr)
            m_pEntityManager->Update(delta);

        if (m_pLevelManager != nullptr)
            m_pLevelManager->Update(delta);
    }

    void GameState::Render(Renderer& renderer)
    {
        /*
        if (m_pEntityManager != nullptr)
            m_pEntityManager->Render(renderer);

        if (m_pLevelManager != nullptr)
            m_pLevelManager->Render(renderer);

        if (m_pTileMap != nullptr)
            m_pTileMap->RenderMap(renderer);
        */
    }
}
