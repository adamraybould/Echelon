#ifndef MAPLAYER_H
#define MAPLAYER_H
#include <tmxlite/TileLayer.hpp>
#include "Graphics/TileMap/Tile.h"
#include "Core/IO/IRenderable.h"
#include "Core/Commons.h"

namespace tmx
{
    class Layer;
    class Tileset;
    class Map;
    class TileLayer;
}

namespace Core { class Renderer; }

namespace Graphics
{
    class Texture2D;
    struct TilesetTexture;

    struct MapTile
    {
        struct Tile
        {
            tmx::TileLayer::Tile TTile;
            Vector2U Position;

            Tile(const tmx::TileLayer::Tile Tile, const Vector2U Position)
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

        Vector2U m_mapSize;
        Vector2U m_tileSize;

    public:
        explicit MapLayer(const tmx::Map& map, const Array<TilesetTexture>& tilesets, tmx::Layer& layer);
        ~MapLayer() override;

        void Render(Renderer& renderer) override;

        void Create();

    private:
        Vector2U GetTilePosition(UInt index) const;
    };
}

#endif //MAPLAYER_H
