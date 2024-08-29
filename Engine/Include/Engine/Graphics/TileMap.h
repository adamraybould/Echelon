#ifndef TILEMAP_H
#define TILEMAP_H
#include "MapLayer.h"
#include "Engine/Utility/Commons.h"

namespace tmx
{
    class Tileset;
    class Map;
}

namespace Core
{
    class Renderer;

    namespace Graphics
    {
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

        public:
            TileMap();
            ~TileMap();

            void RenderMap(Renderer& renderer) const;

            void LoadTileMap(const String& filePath);

        private:
            void LoadTilesets(const tmx::Map& map);
            void LoadLayers(tmx::Map& map, const Array<TilesetTexture>& tilesets);
        };
    }
}

#endif //TILEMAP_H
