#ifndef SPRITE_H
#define SPRITE_H
#include "Texture2D.h"

namespace Core::Graphics
{
    class Sprite : public Texture2D
    {
    private:
        Vector2 m_origin;

    public:
        Sprite(SDL_Texture* texture);

        void SetOrigin(Vector2 origin);

        Vector2& GetOrigin() { return m_origin; }
    };
}

#endif //SPRITE_H
