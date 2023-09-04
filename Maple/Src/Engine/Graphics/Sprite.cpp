#include "Engine/Graphics/Sprite.h"
#include <SDL.h>

MapleEngine::Sprite::Sprite(Texture2D& texture) : m_rTexture(texture)
{
	m_origin = Vector2::Zero();
}

MapleEngine::Sprite::~Sprite()
{
	delete &m_rTexture;
}
