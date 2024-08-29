#include "Engine/Graphics/TileMap.h"

#include <config.h>
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "Engine/Graphics/AssetManager.h"
#include "Engine/Utility/Utility.h"

using namespace tmx;
namespace Core
{
    namespace Graphics
    {
        TileMap::TileMap()
        {
        }

        TileMap::~TileMap()
        {
            for (UInt i = 0; i < m_layers.size(); i++)
            {
                m_layers[i].reset();
            }
        }

        void TileMap::RenderMap(Renderer& renderer) const
        {
            for (UInt i = 0; i < m_layers.size(); i++)
            {
                m_layers[i]->Render(renderer);
            }
        }

        void TileMap::LoadTileMap(const String& filePath)
        {
            String path = std::string(ASSETS_PATH) + "Maps/" + filePath + ".tmx";

            tmx::Map map;
            if (!map.load(path))
            {
                std::cerr << "Error: Failed to load Tilemap at '" << path << "'" << std::endl;
                return;
            }

            LoadTilesets(map);
            if (!m_tilesets.empty())
            {
                LoadLayers(map, m_tilesets);
            }
        }

        void TileMap::LoadTilesets(const tmx::Map& map)
        {
            // Get the Tilesets, ensuring they are not empty
            const Array<tmx::Tileset>& tilesets = map.getTilesets();
            assert(!tilesets.empty());

            for (const tmx::Tileset& tileset : tilesets)
            {
                String tilesetPath = tileset.getImagePath();
                String prefix = ASSETS_PATH;
                String filePath = Utility::RemovePrefix(tilesetPath, prefix);

                Texture2D* texture = &AssetManager::LoadTexture2D(filePath);
                m_tilesets.emplace_back(TilesetTexture(*texture, tileset));
            }
        }

        void TileMap::LoadLayers(tmx::Map& map, const Array<TilesetTexture>& tilesets)
        {
            const Array<UniquePtr<Layer>>& layers = map.getLayers();
            for (UInt i = 0; i < layers.size(); ++i)
            {
                if (layers[i]->getType() == Layer::Type::Tile)
                {
                    m_layers.emplace_back(std::make_unique<MapLayer>(map, tilesets, *layers[i]));
                }
            }
        }
    }
}
