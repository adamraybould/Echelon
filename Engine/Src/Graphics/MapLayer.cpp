#include "Engine/Graphics/MapLayer.h"

#include <SDL_rect.h>
#include <SDL_render.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include "Engine/Graphics/Texture2D.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Graphics/TileMap.h"

namespace Core
{
    namespace Graphics
    {
        MapLayer::MapLayer(const tmx::Map& map, const Array<TilesetTexture>& tilesets, tmx::Layer& layer) : m_map(map), m_tilesets(tilesets), m_layer(layer)
        {
            m_mapSize = Vector2(map.getTileCount().x, map.getTileCount().y);
            m_tileSize = Vector2(map.getTileSize().x, map.getTileSize().y);

            Create();
        }

        void MapLayer::Render(const Renderer& renderer) const
        {
            RenderLayer(renderer);
        }

        void MapLayer::Create()
        {
            const auto& tileLayer = static_cast<tmx::TileLayer&>(m_layer);
            Array<tmx::TileLayer::Tile> tiles = tileLayer.getTiles();

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
                        // Tile is using this Tileset
                        if (m_mapTiles.contains(firstGID))
                        {
                            m_mapTiles.at(firstGID).Tiles.push_back(MapTile::Tile(tiles[i], GetTilePosition(i)));
                        }
                        else
                        {
                            // Map Tiles entry doesn't exist. Create one
                            m_mapTiles.insert(std::make_pair(firstGID, MapTile(tileset.Texture)));
                            m_mapTiles.at(firstGID).Tiles.push_back(MapTile::Tile(tiles[i], GetTilePosition(i)));
                        }
                    }
                }
            }
        }

        void MapLayer::RenderLayer(const Renderer& renderer) const
        {
            for (const auto& map : m_mapTiles)
            {
                for (int i = 0; i < map.second.Tiles.size(); ++i)
                {
                    const MapTile::Tile& tile = map.second.Tiles[i];

                    const Texture2D& texture = map.second.Texture;
                    int tileID = tile.TTile.ID - map.first;

                    int tilesPerRow = texture.GetWidth() / m_tileSize.X;
                    int tileX = (tileID % tilesPerRow) * m_tileSize.X;
                    int tileY = static_cast<int>((tileID / tilesPerRow) * m_tileSize.Y);

                    SDL_Rect srcRect = { tileX, tileY, m_tileSize.X, m_tileSize.Y };

                    Vector2 tileScale = m_tileSize * TILE_SCALE;

                    Vector2 screenPos = Camera::Main->CalculateScreenPosition(tile.Position);
                    screenPos = Vector2(screenPos.X, screenPos.Y);

                    SDL_Rect destRect = { screenPos.X - (tileScale.X * 0.5f), screenPos.Y - (tileScale.Y * 0.5f), tileScale.X , tileScale.Y };

                    SDL_RenderCopy(renderer, &texture.GetRawTexture(), &srcRect, &destRect);
                }
            }
        }

        Vector2 MapLayer::GetTilePosition(const UInt index) const
        {
            float col = index % static_cast<int>(m_mapSize.X);
            float row = index / static_cast<int>(m_mapSize.X);
            int destX = static_cast<int>((col * m_tileSize.X) * TILE_SCALE);
            int destY = static_cast<int>((row * m_tileSize.Y) * TILE_SCALE);

            return Vector2(destX, destY);
        }
    }
}
