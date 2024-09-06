#ifndef TILE_H
#define TILE_H
#include "Core/IO/IRenderable.h"
#include "Core/Maths/Vector2.h"
#include "Graphics/Texture2D.h"

namespace Core
{
    namespace Graphics
    {
        class Tile
        {
        private:
            UInt m_ID;

            Vector2U m_position;
            Vector2U m_size;
            const Texture2D& m_texture;

        public:
            Tile(UInt id, Vector2U position, Vector2U size, const Texture2D& texture);
            void Render(const Renderer& renderer);
        };
    }
}

#endif //TILE_H
