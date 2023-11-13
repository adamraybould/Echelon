#include "Game/World Gen/Block.h"
#include <Engine/Utils/Commons.h>
#include <Engine/Graphics/Texture2D.h>
#include <Engine/Managers/AssetManager.h>

Echelon::Block::Block(UInt ID) : Entity(ID)
{
	Texture2D blockTexture = AssetManager::LoadTexture("objects/rocks.png");
}
