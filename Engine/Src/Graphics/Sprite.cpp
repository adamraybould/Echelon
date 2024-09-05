#include "Engine/Graphics/Sprite.h"

namespace Core
{
    namespace Graphics
    {
        Sprite::Sprite(SDL_Texture* texture) : Texture2D(texture)
        {
            m_origin = Vector2F::Zero();
        }
    }
}
