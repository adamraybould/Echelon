#include "Graphics/TileMap/Tile.h"

#include <SDL_rect.h>
#include <SDL_render.h>
#include "Core/Camera.h"
#include "Core/IO/Renderer.h"
#include "Core/Constants.h"

namespace Core
{
    namespace Graphics
    {
        Tile::Tile(const UInt id, const Vector2U position, const Vector2U size, const Texture2D& texture) : m_ID(id), m_position(position), m_size(size), m_texture(texture)
        {
        }

        void Tile::Render(const Renderer& renderer)
        {
            UInt tilesPerRow = m_texture.GetWidth() / m_size.X;
            UInt tileX = (m_ID % tilesPerRow) * m_size.X;
            UInt tileY = (m_ID / tilesPerRow) * m_size.Y;

            Vector2U tileScale = m_size * TILE_SCALE;
            Vector2F screenPos = Camera::Main->CalculateScreenPosition(m_position);
            screenPos = Vector2(screenPos.X, screenPos.Y);

            const SDL_Rect src = RectU(tileX, tileY, m_size.X, m_size.Y);
            const SDL_Rect dest = RectI(screenPos.X - (tileScale.X * 0.5f), screenPos.Y - (tileScale.Y * 0.5f), tileScale.X, tileScale.Y);

            SDL_RenderCopy(renderer, &m_texture.GetRawTexture(), &src, &dest);
        }
    }
}
