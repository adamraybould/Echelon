#include "Engine/Graphics/SpriteSheet.h"

#include <iostream>

namespace Core::Graphics
{
    SpriteSheet::SpriteSheet(SDL_Texture* texture, const int frameWidth, const int frameHeight, UnorderedMap<String, Animation> animations) : Sprite(texture)
    {
        m_spriteWidth = frameWidth;
        m_spriteHeight = frameHeight;
        m_animations = animations;

        m_frameCount = m_spriteWidth * m_spriteHeight;
    }

    SpriteSheet::~SpriteSheet()
    {
        Sprite::~Sprite();
    }

    RectI SpriteSheet::GetSpriteSource(const UInt frameIndex) const
    {
        int maxXIndex = GetWidth() / m_spriteWidth;
        int xFramePos = (frameIndex % maxXIndex) * m_spriteWidth;
        int yFrameIndex = (int)(frameIndex / maxXIndex);
        int yFramePos = yFrameIndex * m_spriteHeight;

        return { xFramePos, yFramePos, m_spriteWidth, m_spriteHeight };
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
