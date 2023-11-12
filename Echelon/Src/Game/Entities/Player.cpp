#include "Game/Entities/Player.h"
#include <Engine/Entities/Components/SpriteRenderer.h>
#include <Engine/Entities/Components/Animator.h>
#include <Engine/Managers/AssetManager.h>
#include <Engine/Main/Window.h>
#include "Game/Entities/Components/PlayerMovement.h"

Echelon::Player::Player(UInt ID) : Entity(ID)
{
	SpriteSheet& spriteSheet = MapleEngine::AssetManager::LoadSpriteSheet("/characters/player", "Player");

	SpriteRenderer& spriteRenderer = AddComponent<SpriteRenderer>(*this);
	spriteRenderer.SetSprite(spriteSheet);

	Animator& animator = AddComponent<Animator>(*this, spriteRenderer, spriteSheet);
	animator.SetAnimation("idle_Side");

	PlayerMovement& movement = AddComponent<PlayerMovement>(*this);

	Transform.Scale = Vector2(4, 4);
	Transform.Position.X = (SCREEN_WIDTH / 2) + (spriteRenderer.GetSprite().GetOrigin().X * Transform.Scale.X);
	Transform.Position.Y = (SCREEN_HEIGHT / 2) - (spriteRenderer.GetSprite().GetOrigin().Y * (Transform.Scale.Y * 1.35f));
}

void Echelon::Player::Update(float dt)
{
	//Transform.Position += Vector2(0.1f, 0.0f) * dt;

	Entity::Update(dt);
}

void Echelon::Player::Render()
{
	Entity::Render();
}
