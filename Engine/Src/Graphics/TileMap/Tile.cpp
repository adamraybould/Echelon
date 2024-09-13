#include "Graphics/TileMap/Tile.h"

#include <SDL_rect.h>
#include <SDL_render.h>
#include "Core/Camera.h"
#include "Core/IO/Renderer.h"
#include "Core/Constants.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture2D.h"

using namespace Rendering;
namespace Graphics
{
    Tile::Tile(const UInt id, const Vector2U position, const Vector2U size, Texture2D& texture) : m_ID(id), m_position(position), m_size(size), m_sprite(Renderer::CreateSprite(texture))
    {
    }

    void Tile::Render(Renderer& renderer) const
    {
        const UInt tilesPerRow = m_sprite.GetWidth() / m_size.X;
        const UInt tileX = (m_ID % tilesPerRow) * m_size.X;
        const UInt tileY = (m_ID / tilesPerRow) * m_size.Y;

        const Vector2U tileScale = m_size * TILE_SCALE;
        
        const RectF src = RectF(tileX, tileY, m_size.X, m_size.Y);
        const RectF dest = RectF(m_position.X, m_position.Y, tileScale.X, tileScale.Y);

        renderer.Render(&m_sprite, src, dest, 0.0f);
    }
}
