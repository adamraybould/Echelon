#include "Engine/Graphics/Sprite.h"
#include "Engine/Utils/Commons.h"
#include <SDL.h>

MapleEngine::Sprite::Sprite(Texture2D& texture) : m_rTexture(texture)
{
	m_source = Rectangle(0.0f, 0.0f, 48, 48);
	m_origin = Vector2(m_source.Width / 2, m_source.Height / 2);
}

MapleEngine::Sprite::~Sprite()
{
	delete &m_rTexture;
}
