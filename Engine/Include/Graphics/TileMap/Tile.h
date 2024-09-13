#ifndef TILE_H
#define TILE_H
#include "Core/TypeDefs.h"
#include "Core/Maths/Rectangle.h"
#include "Core/Maths/Vector2.h"

namespace Core { class Renderer; }

namespace Graphics
{
    class Texture2D;
    class Sprite;

    class Tile
    {
    private:
        UInt m_ID;

        Sprite& m_sprite;

        Vector2U m_position;
        Vector2U m_size;

        UInt m_tileX;
        UInt m_tileY;
        Vector2U m_tileScale;

        RectF m_src;
        RectF m_dest;

    public:
        Tile(UInt id, Vector2U position, Vector2U size, Texture2D& texture);
        void Render(Renderer& renderer);
    };
}

#endif //TILE_H
