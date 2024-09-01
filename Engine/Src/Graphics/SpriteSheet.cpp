#include "Engine/Graphics/SpriteSheet.h"

#include <iostream>

namespace Core::Graphics
{
    SpriteSheet::SpriteSheet(SDL_Texture* texture, UInt frameWidth, UInt frameHeight, UnorderedMap<String, Animation> animations) : Sprite(texture)
    {
        m_frameWidth = frameWidth;
        m_frameHeight = frameHeight;
        m_animations = animations;

        m_frameCount = m_frameWidth * m_frameHeight;
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

    bool SpriteSheet::IsAnimationValid(const String& animName) const
    {
        return m_animations.contains(animName);
    }

    Animation* SpriteSheet::GetAnimation(const String& animName)
    {
        if (IsAnimationValid(animName))
            return &m_animations[animName];

        std::cerr << "Attempting to access Invalid Animation '" << animName << "'" << std::endl;
        return nullptr;
    }
}
