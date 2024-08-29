#include "Engine/Graphics/AssetManager.h"

#include <fstream>
#include <SDL_image.h>
#include "../../Include/Engine/Core/Renderer.h"
#include "Engine/Graphics/Sprite.h"
#include "Engine/Core/Application.h"
#include <json/json.h>
#include "config.h"

namespace Core::Graphics
{
    const char* ERROR_TEXTURE = "Error.png";
    Renderer* AssetManager::m_renderer;
    Array<UniquePtr<Texture2D>> AssetManager::m_loadedTextures;

    AssetManager::AssetManager(Renderer& renderer)
    {
        m_renderer = &renderer;
    }

    AssetManager::~AssetManager()
    {
        for (auto& texture : m_loadedTextures)
        {
            texture.reset();
        }

        m_loadedTextures.clear();
    }

    Texture2D& AssetManager::LoadTexture2D(const String& filePath)
    {
        SDL_Texture& texture = LoadRawTexture(filePath);
        m_loadedTextures.push_back(std::make_unique<Texture2D>(&texture));

        Texture2D& loadedTexture = *m_loadedTextures.back();
        return loadedTexture;
    }

    Sprite& AssetManager::LoadSprite(const char* filePath)
    {
        std::string texturePath = ASSETS_PATH + std::string(filePath);

        SDL_Texture* texture = IMG_LoadTexture(*m_renderer, texturePath.c_str());
        if (texture == nullptr)
        {
            printf("Failed to load texture: %s\n", SDL_GetError());
            texture = IMG_LoadTexture(*m_renderer, ERROR_TEXTURE);
        }

        m_loadedTextures.push_back(std::make_unique<Sprite>(texture));
        printf("Loaded texture: %s\n", texturePath.c_str());

        Texture2D* loadedTexture = m_loadedTextures.back().get();
        Sprite* loadedSprite = static_cast<Sprite*>(loadedTexture);
        return *loadedSprite;
    }

    SpriteSheet& AssetManager::LoadSpriteSheet(const char* filePath)
    {
        std::string assetPath = ASSETS_PATH + std::string(filePath) + ".sf";

        std::ifstream file(assetPath);
        Json::Reader reader;
        Json::Value data;
        reader.parse(file, data);

        // Read the Sprite Sheet Data
        Json::Value atlasData = data["TextureAtlas"];
        std::string atlasTexture = atlasData["Texture"].asString();
        int frameWidth = atlasData["RegionWidth"].asInt();
        int frameHeight = atlasData["RegionHeight"].asInt();

        // Retrieves Texture from File Path
        std::string path = filePath;
        std::string texturePath = path.substr(0, path.find_last_of('/') + 1) + atlasTexture;

        SDL_Texture& rawTexture = LoadRawTexture(texturePath.c_str());
        m_loadedTextures.push_back(std::make_unique<SpriteSheet>(&rawTexture, frameWidth, frameHeight));

        Texture2D* texture = m_loadedTextures.back().get();
        SpriteSheet* spriteSheet = static_cast<SpriteSheet*>(texture);
        return *spriteSheet;
    }

    SDL_Texture& AssetManager::LoadRawTexture(const String& filePath)
    {
        std::string texturePath = ASSETS_PATH + filePath;

        SDL_Texture* texture = IMG_LoadTexture(*m_renderer, texturePath.c_str());
        if (texture == nullptr)
        {
            std::cerr << "Failed to Load Texture: " << SDL_GetError() << std::endl;

            texturePath = ASSETS_PATH + std::string(ERROR_TEXTURE);
            texture = IMG_LoadTexture(*m_renderer, texturePath.c_str());
        }

        return *texture;
    }
}
