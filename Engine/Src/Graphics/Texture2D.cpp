#include "Graphics/Texture2D.h"

#include <GL/glew.h>
#include <SDL_surface.h>

namespace Graphics
{
    Texture2D::Texture2D(const SDL_Surface& surface)
    {
        m_texture = 0;
        m_width = surface.w;
        m_height = surface.h;

        // Get Surface Format
        if (surface.format->BytesPerPixel == 4)
        {
            m_format = (surface.format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
        }
        else
        {
            m_format = GL_RGB;
        }

        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Create Texture
        glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, surface.pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}
