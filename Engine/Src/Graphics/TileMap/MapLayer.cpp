#include "Graphics/TileMap/MapLayer.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include "Core/IO/Renderer.h"
#include "Graphics/TileMap/Tile.h"
#include "Graphics/TileMap/TileMap.h"
#include "Core/Constants.h"

namespace Graphics
{
    MapLayer::MapLayer(const tmx::Map& map, const Array<TilesetTexture>& tilesets, tmx::Layer& layer) : m_map(map), m_tilesets(tilesets), m_layer(layer)
    {
        m_mapSize = Vector2U(map.getTileCount().x, map.getTileCount().y);
        m_tileSize = Vector2U(map.getTileSize().x, map.getTileSize().y);

        Create();

        SetRenderLayer(RenderLayer::Map);
        Renderer::AddToRenderQueue(*this);
    }

    MapLayer::~MapLayer()
    {
        for (auto& pair : m_tiles)
        {
            for (auto& tiles : pair.second)
            {
                tiles.reset();
            }
        }
    }

    void MapLayer::Render(Renderer& renderer)
    {
        for (auto& pair : m_tiles)
        {
            for (const auto& tiles : pair.second)
            {
                tiles->Render(renderer);
            }
        }
    }

    void MapLayer::Create()
    {
        const auto& tileLayer = static_cast<tmx::TileLayer&>(m_layer);
        const Array<tmx::TileLayer::Tile> tiles = tileLayer.getTiles();

        for (UInt i = 0; i < tiles.size(); ++i)
        {
            UInt tileID = tiles[i].ID;
            if (tileID == 0) // Ignore as Tile is empty
                continue;

            for (const auto& tileset : m_tilesets)
            {
                UInt firstGID = tileset.Tileset.getFirstGID();
                UInt lastGID = firstGID + tileset.Tileset.getTileCount() - 1;

                if (tileID >= firstGID && tileID <= lastGID)
                {
                    UInt id = tileID - firstGID;
                    Vector2U tilePos = GetTilePosition(i);

                    m_tiles[firstGID].push_back(std::make_unique<Tile>(id, tilePos, Vector2F(m_tileSize.X, m_tileSize.Y), tileset.Texture));
                }
            }
        }
    }

    Vector2U MapLayer::GetTilePosition(const UInt index) const
    {
        float col = index % static_cast<int>(m_mapSize.X);
        float row = index / static_cast<int>(m_mapSize.X);
        UInt destX = static_cast<UInt>((col * m_tileSize.X) * TILE_SCALE);
        UInt destY = static_cast<UInt>(((m_mapSize.Y - 1 - row) * m_tileSize.Y) * TILE_SCALE);

        return {destX, destY};
    }
}
