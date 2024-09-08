#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include "Core/TypeDefs.h"

class SDL_Texture;

using namespace Core;
namespace Graphics
{
    class Texture2D
    {
    private:
        SDL_Texture* m_pTexture;

        int m_width;
        int m_height;
        UInt32 m_format;

    public:
        Texture2D(SDL_Texture* texture);
        ~Texture2D();

        void Free();

        SDL_Texture& GetRawTexture() const { return *m_pTexture; }
        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }

        explicit operator SDL_Texture*() const { return m_pTexture; }
    };
}

#endif //TEXTURE2D_H
