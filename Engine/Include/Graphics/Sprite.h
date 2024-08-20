#ifndef SPRITE_H
#define SPRITE_H
#include "Texture2D.h"

struct Rectangle;

namespace Engine::Graphics
{
    class Sprite : public Texture2D
    {
    private:
        Rectangle m_source;
        Vector2 m_origin;

    public:
        Sprite(SDL_Texture* texture);

        void SetSource(Rectangle source);
        void SetOrigin(Vector2 origin);

        Rectangle& GetSource() { return m_source; }
        Vector2& GetOrigin() { return m_origin; }
    };
}

#endif //SPRITE_H
