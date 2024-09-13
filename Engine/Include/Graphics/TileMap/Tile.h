#ifndef TILE_H
#define TILE_H
#include "Core/TypeDefs.h"
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

        Vector2U m_position;
        Vector2U m_size;

        Sprite& m_sprite;

    public:
        Tile(UInt id, Vector2U position, Vector2U size, Texture2D& texture);
        void Render(Renderer& renderer) const;
    };
}

#endif //TILE_H
