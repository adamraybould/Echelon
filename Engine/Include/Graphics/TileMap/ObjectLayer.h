#ifndef MAPCOLLISIONLAYER_H
#define MAPCOLLISIONLAYER_H
#include "Core/TypeDefs.h"
#include "Core/Maths/Vector2.h"

namespace tmx
{
    class Layer;
    class Map;
    class Object;
}

namespace Graphics
{
    class ObjectLayer
    {
    private:
        const tmx::Map& m_map;
        tmx::Layer& m_layer;

    public:
        explicit ObjectLayer(const tmx::Map& map, tmx::Layer& layer);

        void Create();

    private:
        void CreateEntity(const String& prefab, const Vector2F& position);
        Vector2I GetObjectPosition(const tmx::Object& obj) const;
    };

}

#endif //MAPCOLLISIONLAYER_H
