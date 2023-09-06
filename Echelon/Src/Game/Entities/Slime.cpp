#include "Game/Entities/Slime.h"
#include <Engine/Entities/Components/SpriteRenderer.h>
#include <Engine/Entities/Components/Animator.h>
#include <Engine/Managers/AssetManager.h>
#include <Engine/Main/Window.h>

Echelon::Slime::Slime(UInt ID) : Entity(ID)
{
	SpriteSheet& spriteSheet = MapleEngine::AssetManager::LoadSpriteSheet("/characters/slime", "Slime");
	Sprite* sprite = new Sprite(spriteSheet);

	SpriteRenderer& spriteRenderer = AddComponent<SpriteRenderer>(*this);
	spriteRenderer.SetSprite(*sprite);

	Animator& animator = AddComponent<Animator>(*this, spriteRenderer, spriteSheet);
	animator.SetAnimation("move_Long");

	Transform.Scale = Vector2(4, 4);
	Transform.Position.X = (SCREEN_WIDTH / 3) - (sprite->GetOrigin().X * Transform.Scale.X);
	Transform.Position.Y = (SCREEN_HEIGHT / 2) - (sprite->GetOrigin().Y * Transform.Scale.Y);
}

void Echelon::Slime::Update(float dt)
{
	//Transform.Position += Vector2(0.1f, 0.0f) * dt;

	Entity::Update(dt);
}

void Echelon::Slime::Render()
{
	Entity::Render();
}
