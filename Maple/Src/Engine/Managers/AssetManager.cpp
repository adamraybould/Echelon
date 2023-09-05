#include "Engine/Managers/AssetManager.h"
#include "Engine/Main/Application.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const char* ERRORPATH = "Error.png";

SDL_Renderer* MapleEngine::AssetManager::m_pRenderer;

MapleEngine::AssetManager::AssetManager(SDL_Renderer& renderer)
{
	m_pRenderer = &renderer;
}

MapleEngine::AssetManager::~AssetManager()
{
	m_pRenderer = nullptr;
}

MapleEngine::Texture2D& MapleEngine::AssetManager::LoadTexture(const char* path)
{
	CheckAssetManagerInitialized();

	std::string assetPath = "Assets/" + std::string(path);

	SDL_Texture* texture = IMG_LoadTexture(m_pRenderer, assetPath.c_str());
	if (texture == nullptr)
	{
		printf("Texture could not be found at path: %s\n", path);
		texture = IMG_LoadTexture(m_pRenderer, ERRORPATH); // Sets the Texture to be an Error
	}

	Texture2D* texture2D = new Texture2D(*texture);
	return *texture2D;
}

bool MapleEngine::AssetManager::CheckAssetManagerInitialized()
{
	if (m_pRenderer != nullptr)
		return true;
	else
	{
		Application::DisplayError("AssetManager isn't Initialized!", "Engine Error", false);
		return false;
	}
}
