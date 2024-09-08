#include "Graphics/Texture2D.h"

#include <SDL2/SDL_render.h>

namespace Graphics
{
    Texture2D::Texture2D(SDL_Texture* texture)
    {
        m_pTexture = texture;
        SDL_QueryTexture(m_pTexture, &m_format, nullptr, &m_width, &m_height);
    }

    Texture2D::~Texture2D()
    {
        Free();
    }

    void Texture2D::Free()
    {
        SDL_DestroyTexture(m_pTexture);
        m_pTexture = nullptr;
    }
}
