#include "Engine/Graphics/Texture2D.h"
#include "Engine/Main/Application.h"
#include "SDL_image.h"
#include <iostream>

MapleEngine::Texture2D::Texture2D(SDL_Texture* texture, std::string path)
{
	m_pTexture = texture;
	m_texturePath = path;

	// Gets details about the Texture
	SDL_QueryTexture(texture, &m_format, nullptr, &m_width, &m_height);
}

MapleEngine::Texture2D::~Texture2D()
{
	Free();
}

void MapleEngine::Texture2D::Free()
{
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = nullptr;
}

UInt MapleEngine::Texture2D::GetTextureMemorySize()
{
	int bytesPerPixel = SDL_BITSPERPIXEL(m_format) / 8;
	return (m_width * m_height * bytesPerPixel) / 1024.0f;
}
