#ifndef SPRITE_H
#define SPRITE_H
#include "Texture2D.h"
#include "Core/Maths/Vector2.h"

namespace Core
{
    namespace Graphics
    {
        class Sprite : public Texture2D
        {
        private:
            Vector2F m_origin;

        public:
            Sprite(SDL_Texture* texture);

            void SetOrigin(const Vector2F& origin) { m_origin = origin; }
            Vector2F& GetOrigin() { return m_origin; }
        };
    }
}

#endif //SPRITE_H
