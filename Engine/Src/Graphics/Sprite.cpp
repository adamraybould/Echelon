#include "Engine/Graphics/Sprite.h"

namespace Core::Graphics
{
    Sprite::Sprite(SDL_Texture* texture) : Texture2D(texture)
    {
        m_source = Rectangle(0.0f, 0.0f, GetWidth(), GetHeight());
        m_origin = Vector2::Zero();
    }

    void Sprite::SetSource(const Rectangle source)
    {
        m_source = source;
    }

    void Sprite::SetOrigin(const Vector2 origin)
    {
        m_origin = origin;
    }
}
