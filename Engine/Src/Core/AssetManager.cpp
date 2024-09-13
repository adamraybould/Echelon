#include "Core/AssetManager.h"

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <fstream>
#include <filesystem>
#include <json/json.h>
#include <config.h>

#include "Graphics/Texture2D.h"
#include "Core/Application.h"
#include "Core/IO/Renderer.h"
#include "Core/Utility.h"
#include "Graphics/Sprite.h"

namespace fs = std::filesystem;

using namespace Graphics;
namespace Core
{
    const char* ERROR_TEXTURE = "Error.png";
    Renderer* AssetManager::m_renderer;

    Array<SharedPtr<Sprite>> AssetManager::m_pSprites;
    Array<SharedPtr<Texture2D>> AssetManager::m_pTextures;

    AssetManager::AssetManager(Renderer& renderer)
    {
        m_renderer = &renderer;
    }

    AssetManager::~AssetManager()
    {
        for (auto& texture : m_pTextures)
        {
            texture.reset();
        }

        for (auto& sprite : m_pSprites)
        {
            sprite.reset();
        }

        m_pTextures.clear();
        m_pSprites.clear();
    }

    Texture2D& AssetManager::LoadTexture(const String& path)
    {
        SDL_Surface* surface = LoadSurface(ASSETS_PATH + path);

        // Get the Surface Format
        UInt format = 0;
        if (surface->format->BytesPerPixel == 4)
        {
            format = (surface->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
        }
        else
        {
            format = GL_RGB;
        }

        m_pTextures.push_back(std::make_shared<Texture2D>(*surface));
        SDL_FreeSurface(surface);

        return *m_pTextures.back();
    }

    SpriteSheet& AssetManager::LoadSpriteSheet(const String& path)
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
            throw std::invalid_argument("Failed to Read Sprite Sheet: '" + path + "'");
        }

        // Load meta data
        String imagePath = data["meta"]["image"].asString();

        Json::Value& frameData = data["frames"][0];
        UInt spriteWidth = frameData["sourceSize"]["w"].asInt();
        UInt spriteHeight = frameData["sourceSize"]["h"].asInt();

        String pngPath = directoryPath + "/" + imagePath;
        SDL_Surface& surface = *LoadSurface(pngPath);

        const UnorderedMap<String, Animation> animations = GetAnimations(data); // Load Animations
        m_pTextures.push_back(std::make_unique<SpriteSheet>(surface, spriteWidth, spriteHeight, animations));
        return static_cast<SpriteSheet&>(*m_pTextures.back());
    }

    SDL_Surface* AssetManager::LoadSurface(const String& path)
    {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (surface == nullptr)
        {
            std::cerr << "Failed to Load Surface: " << SDL_GetError() << std::endl;

            const String errorPath = ASSETS_PATH + std::string(ERROR_TEXTURE);
            surface = IMG_Load(errorPath.c_str());
        }

        return surface;
    }

    SDL_Texture& AssetManager::LoadRawTexture(const String& filePath)
    {
        /*
        SDL_Texture* texture = IMG_LoadTexture(*m_renderer, filePath.c_str());
        if (texture == nullptr)
        {
            std::cerr << "Failed to Load Texture: " << SDL_GetError() << std::endl;

            String errorPath = ASSETS_PATH + std::string(ERROR_TEXTURE);
            texture = IMG_LoadTexture(*m_renderer, errorPath.c_str());
        }
        return *texture;
        */

        throw std::invalid_argument("File does not exist");
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
