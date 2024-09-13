#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include "Core/TypeDefs.h"

struct SDL_Surface;

namespace Graphics
{
    class Texture2D
    {
    private:
        UInt m_texture;

        UInt m_width;
        UInt m_height;
        UInt m_format;

    public:
        Texture2D(const SDL_Surface& surface);
        ~Texture2D() = default;

        UInt GetWidth() const { return m_width; }
        UInt GetHeight() const { return m_height; }
        UInt GetFormat() const { return m_format; }

        operator UInt() const { return m_texture; }
    };
}

#endif //TEXTURE2D_H
