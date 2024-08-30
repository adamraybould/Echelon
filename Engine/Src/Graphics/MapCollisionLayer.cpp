#include "Engine/Graphics/MapCollisionLayer.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Object.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "Engine/Core/Physics.h"
#include "Engine/Utility/Commons.h"
#include "Engine/Utility/Constants.h"

Core::Graphics::MapCollisionLayer::MapCollisionLayer(const tmx::Map& map, tmx::Layer& layer) : m_map(map), m_layer(layer)
{
    Create();
}

void Core::Graphics::MapCollisionLayer::Create()
{
    const auto& objectLayer = m_layer.getLayerAs<tmx::ObjectGroup>();
    for (const auto& object : objectLayer.getObjects())
    {
        if (object.getShape() == tmx::Object::Shape::Rectangle)
        {
            float width = object.getAABB().width;
            float height = object.getAABB().height;

            Vector2 tileSize = Vector2(m_map.getTileSize().x * TILE_SCALE, m_map.getTileSize().y * TILE_SCALE);
            float positionX = (object.getPosition().x * TILE_SCALE) - (tileSize.X * 0.5f) + width;
            float positionY = (object.getPosition().y * TILE_SCALE) - (tileSize.Y * 0.5f) + height;
            Vector2 position = Vector2(positionX, positionY);

            Physics::CreateStaticBody(position, width, height);
        }
    }
}
