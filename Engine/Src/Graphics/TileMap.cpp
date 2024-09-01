#include "Engine/Graphics/TileMap.h"

#include <config.h>
#include <iostream>
#include <tmxlite/Map.hpp>
#include "Engine/Core/Renderer.h"
#include "Engine/Graphics/AssetManager.h"
#include "Engine/Graphics/MapLayer.h"
#include "Engine/Utility/Utility.h"

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

        void TileMap::Render(Renderer& renderer)
        {
            if (m_pSpaceTexture != nullptr)
            {
                RenderBackground(renderer);
            }

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

            m_mapSize = Vector2(map.getTileCount().x * map.getTileSize().x, map.getTileCount().y * map.getTileSize().y);;

            LoadTilesets(map);
            if (!m_tilesets.empty())
            {
                LoadLayers(map, m_tilesets);
            }

            // Load Space Background
            m_pSpaceTexture = &AssetManager::LoadTexture2D("Tilesets/space.png");

            SetRenderLayer(RenderLayer::TileMap);
            Renderer::AddToRenderQueue(this, GetRenderLayer());
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
            const Array<UniquePtr<tmx::Layer>>& layers = map.getLayers();
            for (UInt i = 0; i < layers.size(); ++i)
            {
                if (layers[i]->getType() == tmx::Layer::Type::Tile)
                {
                    m_layers.emplace_back(std::make_unique<MapLayer>(map, tilesets, *layers[i]));
                }
                else if (layers[i]->getType() == tmx::Layer::Type::Object)
                {
                    m_collisionLayers.emplace_back(std::make_unique<MapCollisionLayer>(map, *layers[i]));
                }
            }
        }

        void TileMap::RenderBackground(const Renderer& renderer) const
        {

            SDL_Rect src = { 0, 0, m_pSpaceTexture->GetWidth(), m_pSpaceTexture->GetHeight() };
            SDL_Rect dst = { 0, 0, SCREEN_WIDTH / Camera::Main->GetZoom(), SCREEN_HEIGHT / Camera::Main->GetZoom() };
            SDL_RenderCopy(renderer, &m_pSpaceTexture->GetRawTexture(), &src, &dst);
        }
    }
}
