#ifndef MAPLAYER_H
#define MAPLAYER_H
#include <tmxlite/TileLayer.hpp>
#include "Engine/Graphics/TileMap/Tile.h"
#include "Engine/Core/Interfaces/IRenderable.h"
#include "Engine/Utility/Commons.h"

namespace tmx
{
    class Layer;
    class Tileset;
    class Map;
    class TileLayer;
}

namespace Core
{
    class Renderer;

    namespace Graphics
    {
        class Texture2D;
        struct TilesetTexture;

        struct MapTile
        {
            struct Tile
            {
                tmx::TileLayer::Tile TTile;
                Vector2 Position;

                Tile(tmx::TileLayer::Tile Tile, Vector2 Position)
                {
                    this->TTile = Tile;
                    this->Position = Position;
                }
            };

            const Texture2D& Texture;
            Array<Tile> Tiles;

            MapTile(const Texture2D& tile_texture) : Texture(tile_texture)
            {
                Tiles = Array<Tile>();
            }
        };

        class MapLayer : public IRenderable
        {
        private:
            const tmx::Map& m_map;
            const Array<TilesetTexture>& m_tilesets;
            tmx::Layer& m_layer;

            UnorderedMap<UInt, Array<UniquePtr<Tile>>> m_tiles;
            UnorderedMap<UInt, MapTile> m_mapTiles;

            Vector2 m_mapSize;
            Vector2 m_tileSize;

        public:
            explicit MapLayer(const tmx::Map& map, const Array<TilesetTexture>& tilesets, tmx::Layer& layer);
            ~MapLayer() override;

            void Render(Renderer& renderer) override;

            void Create();

        private:
            Vector2 GetTilePosition(UInt index) const;
        };
    }
}

#endif //MAPLAYER_H
