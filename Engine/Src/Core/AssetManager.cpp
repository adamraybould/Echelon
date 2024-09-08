#include "Core/AssetManager.h"

#include <fstream>
#include <filesystem>
#include <SDL2/SDL_image.h>
#include <json/json.h>
#include <config.h>

#include "Core/Application.h"
#include "Core/IO/Renderer.h"
#include "Core/Utility.h"

namespace fs = std::filesystem;

using namespace Graphics;
namespace Core
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
        SDL_Texture& texture = LoadRawTexture(ASSETS_PATH + filePath);
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

    SpriteSheet* AssetManager::LoadSpriteSheet(const String& path)
    {
        fs::path filePath(ASSETS_PATH + path);
        fs::path fileDirectory = filePath.parent_path();
        String directoryPath = fileDirectory.string();

        std::ifstream file(filePath.string() + ".json");
        Json::Reader reader;
        Json::Value data;
        if (!reader.parse(file, data))
        {
            std::cerr << "Failed to parse Sprite Sheet: '" << path << "'" << std::endl;
            return nullptr;
        }

        // Load meta data
        String imagePath = data["meta"]["image"].asString();

        Json::Value& frameData = data["frames"][0];
        UInt spriteWidth = frameData["sourceSize"]["w"].asInt();
        UInt spriteHeight = frameData["sourceSize"]["h"].asInt();

        String pngPath = directoryPath + "/" + imagePath;
        SDL_Texture& rawTexture = LoadRawTexture(pngPath);

        const UnorderedMap<String, Animation> animations = GetAnimations(data); // Load Animations
        m_loadedTextures.push_back(std::make_unique<SpriteSheet>(&rawTexture, spriteWidth, spriteHeight, animations));

        Texture2D* texture = m_loadedTextures.back().get();
        SpriteSheet* spriteSheet = static_cast<SpriteSheet*>(texture);

        return spriteSheet;
    }

    SDL_Texture& AssetManager::LoadRawTexture(const String& filePath)
    {
        SDL_Texture* texture = IMG_LoadTexture(*m_renderer, filePath.c_str());
        if (texture == nullptr)
        {
            std::cerr << "Failed to Load Texture: " << SDL_GetError() << std::endl;

            String errorPath = ASSETS_PATH + std::string(ERROR_TEXTURE);
            texture = IMG_LoadTexture(*m_renderer, errorPath.c_str());
        }

        return *texture;
    }

    UnorderedMap<String, Animation> AssetManager::GetAnimations(Json::Value& data)
    {
        UnorderedMap<String, Animation> animations;
        if (data.isMember("frames"))
        {
            for (const Json::Value& frame : data["frames"])
            {
                String filename = frame["filename"].asString();
                const int x = frame["frame"]["x"].asInt();
                const int y = frame["frame"]["y"].asInt();
                const int w = frame["frame"]["w"].asInt();
                const int h = frame["frame"]["h"].asInt();
                const int duration = frame["duration"].asInt();

                String animationName = Utility::SplitString(filename, '#', true);
                if (!animationName.empty())
                {
                    animations[animationName].SetName(animationName);
                    animations[animationName].AddFrame(Frame(x, y, w, h, duration));
                }
            }
        }

        return animations;
    }
}
