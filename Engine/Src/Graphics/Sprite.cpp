#include "Engine/Graphics/Sprite.h"

namespace Core::Graphics
{
    Sprite::Sprite(SDL_Texture* texture) : Texture2D(texture)
    {
        m_origin = Vector2::Zero();
    }

    void Sprite::SetOrigin(const Vector2 origin)
    {
        m_origin = origin;
    }
}
