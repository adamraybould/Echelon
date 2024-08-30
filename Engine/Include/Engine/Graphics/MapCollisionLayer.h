#ifndef MAPCOLLISIONLAYER_H
#define MAPCOLLISIONLAYER_H

namespace tmx
{
    class Layer;
    class Map;
}

namespace Core
{
    namespace Graphics
    {
        class MapCollisionLayer
        {
        private:
            const tmx::Map& m_map;
            tmx::Layer& m_layer;

        public:
            explicit MapCollisionLayer(const tmx::Map& map, tmx::Layer& layer);

            void Create();
        };

    }
}

#endif //MAPCOLLISIONLAYER_H
