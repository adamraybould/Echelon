#include "Graphics/Sprite.h"

namespace Graphics
{
    Sprite::Sprite(SDL_Texture* texture) : Texture2D(texture)
    {
        m_origin = Vector2F::Zero();
    }
}
