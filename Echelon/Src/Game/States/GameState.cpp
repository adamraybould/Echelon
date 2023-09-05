#include "Game/States/GameState.h"
#include <Engine/Entities/Components/SpriteRenderer.h>
#include <Engine/Managers/AssetManager.h>
#include <Engine/Main/Window.h>

Echelon::GameState::GameState()
{
	player = new MapleEngine::Entity(0);
}

void Echelon::GameState::Initialize()
{
	Texture2D& texture = MapleEngine::AssetManager::LoadTexture("/characters/player.png");
	Sprite* sprite = new Sprite(texture);

	SpriteRenderer& spriteRenderer = player->AddComponent<SpriteRenderer>();
	spriteRenderer.SetSprite(*sprite);

	player->Transform.Scale = Vector2(4, 4);
	player->Transform.Position.X = (SCREEN_WIDTH / 2) - (sprite->GetOrigin().X * player->Transform.Scale.X);
	player->Transform.Position.Y = (SCREEN_HEIGHT / 2) - (sprite->GetOrigin().Y * player->Transform.Scale.Y);	
}

void Echelon::GameState::Update(float dt)
{
	player->Transform.Position += Vector2(0.1f, 0.0f) * dt;

	player->Update(dt);
}

void Echelon::GameState::Render()
{
	player->Render();
}
