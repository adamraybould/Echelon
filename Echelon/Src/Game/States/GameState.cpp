#include "Game/States/GameState.h"
#include <Engine/Managers/AssetManager.h>

Echelon::GameState::GameState()
{
	player = new Player(0);
	slime = new Slime(1);
}

Echelon::GameState::~GameState()
{
	delete player;
	delete slime;
}

void Echelon::GameState::Initialize()
{
}

void Echelon::GameState::Update(float dt)
{
	player->Update(dt);
	slime->Update(dt);
}

void Echelon::GameState::Render()
{
	player->Render();
	slime->Render();
}
