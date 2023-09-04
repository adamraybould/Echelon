#include "GameState.h"
#include <Engine/Entities/Components/SpriteRenderer.h>
#include <iostream>

Echelon::GameState::GameState()
{
	player = new MapleEngine::Entity(0);
}

void Echelon::GameState::Initialize()
{
	player->Transform().Position = Vector2(-830.0f, -600.0f);
	player->Transform().Scale = Vector2(1.8f, 1.8f);

	Texture2D* texture = new Texture2D("Twilight.jpg");
	Sprite* sprite = new Sprite(*texture);

	SpriteRenderer& spriteRenderer = player->AddComponent<SpriteRenderer>();
	spriteRenderer.SetSprite(*sprite);
}

void Echelon::GameState::Update(float dt)
{
	player->Update(dt);
}

void Echelon::GameState::Render()
{
	player->Render();
}
