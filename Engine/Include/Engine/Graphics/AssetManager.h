#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Texture2D.h"

namespace Core
{
    class Application;
    class Renderer;

    namespace Graphics
    {
        class AssetManager
        {
        private:
            static Renderer* m_renderer;
            static Array<UniquePtr<Texture2D>> m_loadedTextures; // An Array of Loaded Textures

        public:
            AssetManager(Renderer& renderer);
            ~AssetManager();

            /* Loads a Raw SDL Texture */
            static SDL_Texture& LoadRawTexture(const char* filePath);

            static Texture2D& LoadTexture2D(const char* filePath);
            static Sprite& LoadSprite(const char* filePath);

            /* Loads a Sprite Sheet through a .SF file */
            static SpriteSheet& LoadSpriteSheet(const char* filePath);
        };
    }
}

#endif //ASSETMANAGER_H
