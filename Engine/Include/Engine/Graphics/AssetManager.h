#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Texture2D.h"

namespace Json
{
    class Value;
}

namespace Core
{
    class Application;
    class Renderer;

    namespace Graphics
    {
        struct MetaData
        {
            String ImagePath;
            int ImageWidth;
            int ImageHeight;

            MetaData(String imagePath, const int imageWidth, const int imageHeight): ImagePath(imagePath), ImageWidth(imageWidth), ImageHeight(imageHeight) {}
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
            static Array<UniquePtr<Texture2D>> m_loadedTextures; // An Array of Loaded Textures

        public:
            AssetManager(Renderer& renderer);
            ~AssetManager();

            static Texture2D& LoadTexture2D(const String& filePath);
            static Sprite& LoadSprite(const char* filePath);

            static SpriteSheet* LoadSpriteSheet(const String& path);

        private:
            /* Loads a Raw SDL texture */
            static SDL_Texture& LoadRawTexture(const String& filePath);

            static UnorderedMap<String, Animation> GetAnimations(Json::Value& data);
        };
    }
}

#endif //ASSETMANAGER_H
