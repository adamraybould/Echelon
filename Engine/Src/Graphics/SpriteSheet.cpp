#include "Engine/Graphics/SpriteSheet.h"

namespace Core::Graphics
{
    SpriteSheet::SpriteSheet(SDL_Texture* texture, UInt frameWidth, UInt frameHeight): Sprite(texture)
    {
        m_frameWidth = frameWidth;
        m_frameHeight = frameHeight;
        m_frameCount = m_frameWidth * m_frameHeight;

        SetSource(GetSpriteSource(0));
    }

    SpriteSheet::~SpriteSheet()
    {
        Sprite::~Sprite();
    }

    Rectangle SpriteSheet::GetSpriteSource(UInt frameIndex) const
    {
        int maxXIndex = GetWidth() / m_frameWidth;
        int xFramePos = (frameIndex % maxXIndex) * m_frameWidth;
        int yFrameIndex = (int)(frameIndex / maxXIndex);
        int yFramePos = yFrameIndex * m_frameHeight;

        return Rectangle(xFramePos, yFramePos, m_frameWidth, m_frameHeight);
    }
}
