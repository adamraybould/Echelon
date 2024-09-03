#include "Engine/Graphics/TileMap/Tile.h"

#include <SDL_rect.h>
#include <SDL_render.h>
#include "Engine/Core/Camera.h"
#include "Engine/Core/Renderer.h"

namespace Core
{
    namespace Graphics
    {
        Tile::Tile(const UInt id, const Vector2 position, const Vector2 size, const Texture2D& texture) : m_ID(id), m_position(position), m_size(size), m_texture(texture)
        {
        }

        void Tile::Render(const Renderer& renderer)
        {
            int tilesPerRow = m_texture.GetWidth() / m_size.X;
            int tileX = (m_ID % tilesPerRow) * m_size.X;
            int tileY = static_cast<int>((m_ID / tilesPerRow) * m_size.Y);

            SDL_Rect srcRect = { tileX, tileY, m_size.X, m_size.Y };

            Vector2 tileScale = m_size * TILE_SCALE;
            Vector2 screenPos = Camera::Main->CalculateScreenPosition(m_position);
            screenPos = Vector2(screenPos.X, screenPos.Y);

            SDL_Rect destRect = { screenPos.X - (tileScale.X * 0.5f), screenPos.Y - (tileScale.Y * 0.5f), tileScale.X , tileScale.Y };

            SDL_RenderCopy(renderer, &m_texture.GetRawTexture(), &srcRect, &destRect);
        }
    }
}
