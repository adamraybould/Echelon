#include "Engine/Managers/AssetManager.h"
#include "Engine/Main/Application.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <fstream>
#include <json/json.h>

const char* ERRORPATH = "Error.png";

SDL_Renderer* MapleEngine::AssetManager::m_pRenderer;
std::map<std::string, MapleEngine::SpriteSheet*> MapleEngine::AssetManager::m_spriteSheets;

MapleEngine::AssetManager::AssetManager(SDL_Renderer& renderer)
{
	m_pRenderer = &renderer;
}

MapleEngine::AssetManager::~AssetManager()
{
	// Clears up the Sprite Sheets
	for (auto& pair : m_spriteSheets)
	{
		delete pair.second;
	}
	m_spriteSheets.clear();

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

MapleEngine::SpriteSheet& MapleEngine::AssetManager::LoadSpriteSheet(const char* path, const char* sheetName)
{
	CheckAssetManagerInitialized();

	//TODO: Store Sprite Sheet in Array.

	// Load the JSON .sf file for the Sprite Sheet.
	std::string fileType = ".sf";
	std::string assetPath = "Assets" + std::string(path) + fileType;
	
	std::ifstream file(assetPath);
	Json::Reader reader;
	Json::Value data;
	reader.parse(file, data);

	// Read the Sprite Sheet data
	Json::Value atlasData = data["textureAtlas"];
	std::string atlasTexture = atlasData["texture"].asString();
	int spriteWidth = atlasData["regionWidth"].asInt();
	int spriteHeight = atlasData["regionHeight"].asInt();
	
	// Gets the Texture from the same file location
	std::string tPath = std::string(path);
	std::string texturePath = tPath.substr(0, tPath.find_last_of('/') + 1) + atlasTexture;
	Texture2D& sheetTexture = LoadTexture(texturePath.c_str());
	SpriteSheet* spriteSheet = new SpriteSheet(sheetTexture, spriteWidth, spriteHeight);

	// Load Animations if there is any
	if (data.isMember("cycles"))
	{
		const Json::Value cycles = data["cycles"];
		for (const auto& animationName : cycles.getMemberNames())
		{
			Animation animation = Animation(animationName.c_str());

			// Loop through every frame in the Animation and add it
			const Json::Value frames = cycles[animationName]["frames"];
			for (const auto& frame : frames)
			{
				animation.AddAnimationFrame(Frame(frame.asInt()));
			}

			// Assigns the Animation to the Sprite Sheet
			spriteSheet->AddAnimation(animation);
		}
	}

	m_spriteSheets.insert(std::make_pair(sheetName, spriteSheet));
	return *spriteSheet;
}

bool MapleEngine::AssetManager::CheckAssetManagerInitialized()
{
	if (m_pRenderer != nullptr)
		return true;
	else
	{
		Application::DisplayError("AssetManager isn't Initialized!", "Engine Error", false);
		exit(1);
		return false;
	}
}