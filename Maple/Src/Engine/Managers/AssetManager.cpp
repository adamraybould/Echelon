#include "Engine/Managers/AssetManager.h"
#include "Engine/Main/Application.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <fstream>
#include <json/json.h>

const char* ERRORPATH = "Error.png";

MultiCastEvent<void, MapleEngine::Texture2D*> MapleEngine::AssetManager::OnTextureLoaded;
std::map<std::string, UniquePtr<MapleEngine::SpriteSheet>> MapleEngine::AssetManager::m_loadedSpriteSheets;
std::vector<UniquePtr<MapleEngine::Texture2D>> MapleEngine::AssetManager::m_loadedTextures;

MapleEngine::AssetManager::~AssetManager()
{
	// Clears up the Sprite Sheets
	for (auto& pair : m_loadedSpriteSheets)
	{
		pair.second.reset();
	}

	for (auto& texture : m_loadedTextures)
	{
		texture.reset();
	}

	m_loadedSpriteSheets.clear();
	m_loadedTextures.clear();
}

MapleEngine::Texture2D& MapleEngine::AssetManager::LoadTexture(const char* path)
{
	CheckAssetManagerInitialized();

	std::string assetPath = "Assets/" + std::string(path);
	SDL_Renderer& renderer = Application::GetInstance().GetRenderer();

	SDL_Texture* texture = IMG_LoadTexture(&renderer, assetPath.c_str());
	if (texture == nullptr)
	{
		printf("Texture could not be found at path: %s\n", path);
		texture = IMG_LoadTexture(&renderer, ERRORPATH); // Sets the Texture to be an Error
	}

	m_loadedTextures.push_back(std::make_unique<Texture2D>(texture, assetPath));
	std::cout << "--- Loaded Texture: " << assetPath << " | Size: " << m_loadedTextures.back().get()->GetTextureMemorySize() << "KB ---" << std::endl;

	Texture2D* loadedTexture = m_loadedTextures.back().get();

	return *loadedTexture;
}

MapleEngine::SpriteSheet& MapleEngine::AssetManager::LoadSpriteSheet(const char* path, const char* sheetName)
{
	CheckAssetManagerInitialized();

	// Load the JSON .sf file for the Sprite Sheet.
	std::string fileType = ".sf";
	std::string assetPath = "Assets" + std::string(path) + fileType;
	
	std::ifstream file(assetPath);
	Json::Reader reader;
	Json::Value data;
	reader.parse(file, data);

	// Read the Sprite Sheet data
	Json::Value atlasData = data["TextureAtlas"];
	std::string atlasTexture = atlasData["Texture"].asString();
	int spriteWidth = atlasData["RegionWidth"].asInt();
	int spriteHeight = atlasData["RegionHeight"].asInt();
	
	// Gets the Texture from the same file location
	std::string tPath = std::string(path);
	std::string texturePath = tPath.substr(0, tPath.find_last_of('/') + 1) + atlasTexture;
	Texture2D& sheetTexture = LoadTexture(texturePath.c_str());
	UniquePtr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(sheetTexture, spriteWidth, spriteHeight);

	// Load Animations if there is any
	if (data.isMember("Cycles"))
	{
		const Json::Value cycles = data["Cycles"];
		for (const auto& animationName : cycles.getMemberNames())
		{
			Animation animation = Animation(animationName.c_str());

			// Loop through every frame in the Animation and add it
			const Json::Value frames = cycles[animationName]["Frames"];
			for (const auto& frame : frames)
			{
				animation.AddAnimationFrame(Frame(frame.asInt()));
			}

			// Assigns the Animation to the Sprite Sheet
			spriteSheet->AddAnimation(animation);
		}
	}

	m_loadedSpriteSheets.insert(std::make_pair(sheetName, std::move(spriteSheet)));
	return *m_loadedSpriteSheets[sheetName];
}

bool MapleEngine::AssetManager::CheckAssetManagerInitialized()
{
	if (&Application::GetInstance().GetRenderer() != nullptr)
		return true;
	else
	{
		Application::DisplayError("AssetManager Not Initialized!", "Engine Error", false);
		exit(1);
		return false;
	}
}