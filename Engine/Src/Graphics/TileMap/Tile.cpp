#include "Graphics/TileMap/Tile.h"


#include "Core/Camera.h"
#include "Core/IO/Renderer.h"
#include "Core/Constants.h"
#include "Graphics/Sprite.h"

using namespace Rendering;
namespace Graphics
{
    Tile::Tile(const UInt id, const Vector2U position, const Vector2U size, Texture2D& texture) : m_ID(id), m_sprite(Renderer::CreateSprite(texture)), m_position(position), m_size(size)
    {
        const UInt tilesPerRow = m_sprite.GetWidth() / m_size.X;
        m_tileX = (m_ID % tilesPerRow) * m_size.X;
        m_tileY = (m_ID / tilesPerRow) * m_size.Y;
        m_tileScale = m_size * TILE_SCALE;

        m_src = RectF(m_tileX, m_tileY, m_size.X, m_size.Y);
        m_dest = RectF(m_position.X, m_position.Y, m_tileScale.X, m_tileScale.Y);
    }

    void Tile::Render(Renderer& renderer)
    {
        renderer.Render(&m_sprite, m_src, m_dest, 0.0f);
    }
}
