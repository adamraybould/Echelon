#include "Graphics/TileMap/ObjectLayer.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Object.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "Core/Physics.h"
#include "Systems/EntityManager.h"
#include "Core/Constants.h"
#include "Scene/World.h"

using namespace Systems;
namespace Graphics
{
    ObjectLayer::ObjectLayer(const tmx::Map& map, tmx::Layer& layer) : m_map(map), m_layer(layer)
    {
        Create();
    }

    void ObjectLayer::Create() const
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
                    CreateEntity(property.getStringValue(),Vector2F(GetObjectPosition(object).X, GetObjectPosition(object).Y));
                    break;
                }
            }

            if (isEntity)
                continue;

            // Create Collisions
            if (object.getShape() == tmx::Object::Shape::Rectangle)
            {
                const float width = object.getAABB().width;
                const float height = object.getAABB().height;

                const Vector2U tileSize = Vector2(m_map.getTileSize().x * TILE_SCALE, m_map.getTileSize().y * TILE_SCALE);
                const float positionX = (object.getPosition().x * TILE_SCALE) - (tileSize.X * 0.5f) + width;
                const float positionY = ((m_map.getBounds().height - object.getPosition().y) * TILE_SCALE) - (tileSize.Y * 0.5f) - height;
                const Vector2F position = Vector2F(positionX, positionY);

                Physics::CreateStaticBody(position, width, height);
            }
        }
    }

    void ObjectLayer::CreateEntity(const String& prefab, const Vector2F& position) const
    {
        const GUID entity = World::SpawnPrefab(ScriptCore::Instance()->GetLuaState(), prefab);
        EntityManager::GetEntityByGUID(entity)->GetTransform().SetWorldPosition(position);
    }

    Vector2F ObjectLayer::GetObjectPosition(const tmx::Object& obj) const
    {
        Vector2U tileSize = Vector2U(obj.getAABB().width * TILE_SCALE, obj.getAABB().height * TILE_SCALE);
        float positionX = (obj.getPosition().x * TILE_SCALE) + (tileSize.X * 0.5f) - m_map.getTileSize().x;
        float positionY = ((m_map.getBounds().height - obj.getPosition().y) * TILE_SCALE) + (tileSize.Y * 0.5f) - m_map.getTileSize().y;
        return { positionX, positionY };
    }
}
