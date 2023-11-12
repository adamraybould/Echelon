#include "Game/States/GameState.h"
#include <Engine/Managers/AssetManager.h>

Echelon::GameState::GameState()
{
	m_pLevel = std::make_unique<TestLevel>();
}

Echelon::GameState::~GameState()
{
	m_pLevel.reset();
}

void Echelon::GameState::Initialize()
{
	m_pLevel->InitializeLevel();
}

void Echelon::GameState::Update(float dt)
{
	m_pLevel->Update(dt);
}

void Echelon::GameState::Render()
{
	m_pLevel->Render();
}
