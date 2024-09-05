#ifndef TILEMAP_H
#define TILEMAP_H
#include "ObjectLayer.h"
#include "Engine/Core/Interfaces/IRenderable.h"
#include "Engine/Utility/Commons.h"

namespace tmx
{
    class Tileset;
}

namespace Core
{
    class Renderer;

    namespace Graphics
    {
        class MapLayer;
        class Texture2D;

        struct TilesetTexture
        {
            const Texture2D& Texture;
            const tmx::Tileset& Tileset;

            TilesetTexture(const Texture2D& texture, const tmx::Tileset& tileset) : Texture(texture), Tileset(tileset)
            {

            }
        };

        class TileMap
        {
        private:
            Array<TilesetTexture> m_tilesets;
            Array<UniquePtr<MapLayer>> m_layers;
            Array<UniquePtr<ObjectLayer>> m_collisionLayers;

            Vector2U m_mapSize;
            Texture2D* m_pSpaceTexture;

        public:
            TileMap();
            ~TileMap();

            void Render(Renderer& renderer);

            void LoadTileMap(const String& filePath);

        private:
            void LoadTilesets(const tmx::Map& map);
            void LoadLayers(tmx::Map& map, const Array<TilesetTexture>& tilesets);

            void RenderBackground(const Renderer& renderer) const;
        };
    }
}

#endif //TILEMAP_H
