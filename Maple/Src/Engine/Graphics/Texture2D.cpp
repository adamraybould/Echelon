#include "Engine/Graphics/Texture2D.h"
#include "Engine/Main/Application.h"
#include "SDL_image.h"
#include <iostream>

MapleEngine::Texture2D::Texture2D(const char* path)
{
	m_pTexture = IMG_LoadTexture(Application::GetInstance().GetRenderer(), path);
	if (m_pTexture == nullptr)
	{
		std::cout << "Error loading Texture at path: " << path << std::endl;
		return;
	}

	// Gets details about the Texture
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_width, &m_height);
}

MapleEngine::Texture2D::Texture2D(SDL_Texture& texture)
{
	m_pTexture = &texture;

	// Gets details about the Texture
	SDL_QueryTexture(&texture, nullptr, nullptr, &m_width, &m_height);
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
