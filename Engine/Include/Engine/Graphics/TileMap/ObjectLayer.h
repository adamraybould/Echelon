#ifndef MAPCOLLISIONLAYER_H
#define MAPCOLLISIONLAYER_H
#include <string>

#include "Engine/Core/Maths/Vector2.h"

using String = std::string;

namespace tmx
{
    class Layer;
    class Map;
    class Object;
}

namespace Core
{
    using namespace Maths;
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
            void CreateEntity(const String& prefab, const Vector2& position);
            Vector2 GetObjectPosition(const tmx::Object& obj) const;
        };

    }
}

#endif //MAPCOLLISIONLAYER_H
