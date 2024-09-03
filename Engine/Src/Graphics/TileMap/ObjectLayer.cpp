#include "Engine/Graphics/TileMap/ObjectLayer.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Object.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "Engine/Core/Engine.h"
#include "Engine/Core/Physics.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/ECS/Components/Rigidbody.h"
#include "Engine/Core/Systems/EntityManager.h"
#include "Engine/Utility/Commons.h"
#include "Engine/Utility/Constants.h"

Core::Graphics::ObjectLayer::ObjectLayer(const tmx::Map& map, tmx::Layer& layer) : m_map(map), m_layer(layer)
{
    Create();
}

void Core::Graphics::ObjectLayer::Create()
{
    const auto& objectLayer = m_layer.getLayerAs<tmx::ObjectGroup>();
    for (const auto& object : objectLayer.getObjects())
    {
        bool isEntity = false;
        const auto& properties = object.getProperties();
        for (const auto& property : properties)
        {
            if (property.getName() == "Prefab")
            {
                isEntity = true;
                CreateEntity(property.getStringValue(), GetObjectPosition(object));
                break;
            }
        }

        if (isEntity)
            continue;

        // Create Collisions
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

void Core::Graphics::ObjectLayer::CreateEntity(const String& prefab, const Vector2& position)
{
    GUID entity = Engine::SpawnPrefab(ScriptCore::Instance()->GetLuaState(), prefab);
    EntityManager::GetEntityByGUID(entity)->GetTransform().SetWorldPosition(position);
}

Vector2 Graphics::ObjectLayer::GetObjectPosition(const tmx::Object& obj) const
{
    Vector2 tileSize = Vector2(obj.getAABB().width * TILE_SCALE, obj.getAABB().height * TILE_SCALE);
    float positionX = (obj.getPosition().x * TILE_SCALE) + (tileSize.X * 0.5f) - m_map.getTileSize().x;
    float positionY = (obj.getPosition().y * TILE_SCALE) - (tileSize.Y * 0.5f) - m_map.getTileSize().y;
    return Vector2(positionX, positionY);
}
