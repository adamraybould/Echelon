#ifndef TILE_H
#define TILE_H
#include "Engine/Core/Interfaces/IRenderable.h"
#include "Engine/Core/Maths/Vector2.h"
#include "Engine/Graphics/Texture2D.h"

namespace Core
{
    using namespace Maths;
    namespace Graphics
    {
        class Tile
        {
        private:
            UInt m_ID;

            Vector2 m_position;
            Vector2 m_size;
            const Texture2D& m_texture;

        public:
            Tile(UInt id, Vector2 position, Vector2 size, const Texture2D& texture);
            void Render(const Renderer& renderer);
        };
    }
}

#endif //TILE_H
