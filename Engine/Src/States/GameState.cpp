#include "States/GameState.h"
#include "Graphics/TileMap/TileMap.h"
#include "Scene/LevelManager.h"
#include "Scene/World.h"

using namespace Systems;
using namespace Graphics;
using namespace Scene;

namespace Core::States
{
    GameState::GameState()
    {
        m_pLevelManager = std::make_unique<LevelManager>();
        m_pWorld = std::make_unique<World>();
    }

    GameState::~GameState()
    {
        m_pLevelManager.reset();
        m_pWorld.reset();
    }

    void GameState::Setup()
    {
    }

    void GameState::Initialise()
    {
        ScriptCore::Instance()->LoadScript("game.lua");

        if (m_pWorld != nullptr)
            m_pWorld->Initialise();
    }

    void GameState::Update(const float delta)
    {
        if (m_pWorld != nullptr)
            m_pWorld->Update(delta);
    }
}
