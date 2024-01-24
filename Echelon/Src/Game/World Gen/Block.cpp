#include "Game/World Gen/Block.h"
#include <Engine/Entities/Components/SpriteRenderer.h>
#include <Engine/Managers/AssetManager.h>

Echelon::Block::Block(UInt ID) : Entity(ID)
{
	SpriteSheet& spriteSheet = AssetManager::LoadSpriteSheet("/objects/rocks", "Rocks");

	SpriteRenderer& spriteRenderer = AddComponent<SpriteRenderer>(*this);
	spriteRenderer.SetSprite(spriteSheet);
	spriteRenderer.GetSprite().SetSpriteSource(spriteSheet.GetSprite(4));

	Transform.Position = Vector2(200, 200);
}
