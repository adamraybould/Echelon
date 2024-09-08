#include "Graphics/TileMap/ObjectLayer.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Object.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "Core/Scripting/Engine.h"
#include "Core/Physics.h"
#include "Systems/EntityManager.h"
#include "Core/Constants.h"

using namespace Systems;
namespace Graphics
{
    ObjectLayer::ObjectLayer(const tmx::Map& map, tmx::Layer& layer) : m_map(map), m_layer(layer)
    {
        Create();
    }

    void ObjectLayer::Create()
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
                    CreateEntity(property.getStringValue(),
                                 Vector2F(GetObjectPosition(object).X, GetObjectPosition(object).Y));
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

                Vector2U tileSize = Vector2(m_map.getTileSize().x * TILE_SCALE, m_map.getTileSize().y * TILE_SCALE);
                UInt positionX = (object.getPosition().x * TILE_SCALE) - (tileSize.X * 0.5f) + width;
                UInt positionY = (object.getPosition().y * TILE_SCALE) - (tileSize.Y * 0.5f) + height;
                Vector2F position = Vector2F(positionX, positionY);

                Physics::CreateStaticBody(position, width, height);
            }
        }
    }

    void ObjectLayer::CreateEntity(const String& prefab, const Vector2F& position)
    {
        const GUID entity = Engine::SpawnPrefab(ScriptCore::Instance()->GetLuaState(), prefab);
        EntityManager::GetEntityByGUID(entity)->GetTransform().SetWorldPosition(position);
    }

    Vector2I ObjectLayer::GetObjectPosition(const tmx::Object& obj) const
    {
        Vector2U tileSize = Vector2U(obj.getAABB().width * TILE_SCALE, obj.getAABB().height * TILE_SCALE);
        int positionX = (obj.getPosition().x * TILE_SCALE) + (tileSize.X * 0.5f) - m_map.getTileSize().x;
        int positionY = (obj.getPosition().y * TILE_SCALE) - (tileSize.Y * 0.5f) - m_map.getTileSize().y;
        return {positionX, positionY};
    }
}
