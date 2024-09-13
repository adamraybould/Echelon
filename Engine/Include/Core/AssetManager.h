#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "Graphics/SpriteSheet.h"
#include "Graphics/Texture2D.h"

struct SDL_Surface;
struct SDL_Texture;

namespace Graphics { class Texture2D; class Sprite; }
namespace Json { class Value; }

namespace Core
{
    class Application;
    class Renderer;

    struct MetaData
    {
        String ImagePath;
        int ImageWidth;
        int ImageHeight;

        MetaData(const String& imagePath, const int imageWidth, const int imageHeight): ImagePath(imagePath), ImageWidth(imageWidth), ImageHeight(imageHeight) {}
    };

    class AssetManager
    {
    private:
        struct FrameData
        {
            String Name;
            int Frame;

            bool IsEmpty() const { return Name.empty(); }
        };

    private:
        static Renderer* m_renderer;
        static Array<SharedPtr<Graphics::Sprite>> m_pSprites;
        static Array<SharedPtr<Graphics::Texture2D>> m_pTextures;

    public:
        AssetManager(Renderer& renderer);
        ~AssetManager();

        static Graphics::Texture2D& LoadTexture(const String& path);
        static Graphics::SpriteSheet& LoadSpriteSheet(const String& path);

    private:
        static SDL_Surface* LoadSurface(const String& path);

        /* Loads a Raw SDL texture */
        static SDL_Texture& LoadRawTexture(const String& filePath);

        static UnorderedMap<String, Graphics::Animation> GetAnimations(Json::Value& data);
    };
}

#endif //ASSETMANAGER_H
