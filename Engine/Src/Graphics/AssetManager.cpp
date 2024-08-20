#include "Graphics/AssetManager.h"

#include <fstream>
#include <SDL_image.h>
#include "Graphics/Sprite.h"
#include "Main/Application.h"
#include <json/json.h>

namespace Engine::Graphics
{
    const char* ERROR_TEXTURE = "Error.png";

    Application* AssetManager::m_application;
    Array<UniquePtr<Texture2D>> AssetManager::m_loadedTextures;

    AssetManager::AssetManager(Application& application)
    {
        m_application = &application;
    }

    AssetManager::~AssetManager()
    {
        for (auto& texture : m_loadedTextures)
        {
            texture.reset();
        }

        m_loadedTextures.clear();
    }

    SDL_Texture& AssetManager::LoadRawTexture(const char* filePath)
    {
        std::string texturePath = "Assets/" + std::string(filePath);
        SDL_Renderer* renderer = &m_application->GetRenderer();

        SDL_Texture* texture = IMG_LoadTexture(renderer, texturePath.c_str());
        if (texture == nullptr)
        {
            printf("Failed to load texture: %s\n", SDL_GetError());
            texture = IMG_LoadTexture(renderer, ERROR_TEXTURE);
        }

        return *texture;
    }

    Texture2D& AssetManager::LoadTexture2D(const char* filePath)
    {
        std::string texturePath = "Assets/" + std::string(filePath);
        SDL_Renderer* renderer = &m_application->GetRenderer();

        SDL_Texture* texture = IMG_LoadTexture(renderer, texturePath.c_str());
        if (texture == nullptr)
        {
            printf("Failed to load texture: %s\n", SDL_GetError());
            texture = IMG_LoadTexture(renderer, ERROR_TEXTURE);
        }

        m_loadedTextures.push_back(std::make_unique<Texture2D>(texture));
        printf("Loaded texture: %s\n", texturePath.c_str());

        Texture2D* loadedTexture = m_loadedTextures.back().get();
        return *loadedTexture;
    }

    Sprite& AssetManager::LoadSprite(const char* filePath)
    {
        std::string texturePath = "Assets/" + std::string(filePath);
        SDL_Renderer* renderer = &m_application->GetRenderer();

        SDL_Texture* texture = IMG_LoadTexture(renderer, texturePath.c_str());
        if (texture == nullptr)
        {
            printf("Failed to load texture: %s\n", SDL_GetError());
            texture = IMG_LoadTexture(renderer, ERROR_TEXTURE);
        }

        m_loadedTextures.push_back(std::make_unique<Sprite>(texture));
        printf("Loaded texture: %s\n", texturePath.c_str());

        Texture2D* loadedTexture = m_loadedTextures.back().get();
        Sprite* loadedSprite = static_cast<Sprite*>(loadedTexture);
        return *loadedSprite;
    }

    SpriteSheet& AssetManager::LoadSpriteSheet(const char* filePath)
    {
        std::string assetPath = "Assets/" + std::string(filePath) + ".sf";

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
}
