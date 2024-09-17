#include "Graphics/SpriteSheet.h"

#include <iostream>
#include <SDL2/SDL.h>

namespace Graphics
{
    SpriteSheet::SpriteSheet(const SDL_Surface& surface, const int frameWidth, const int frameHeight, const Array<Frame>& frames, const UnorderedMap<String, Animation>& animations) : Texture2D(surface)
    {
        m_spriteWidth = frameWidth;
        m_spriteHeight = frameHeight;

        m_frames = frames;
        m_animations = animations;

        m_frameCount = m_spriteWidth * m_spriteHeight;
    }

    SpriteSheet::~SpriteSheet()
    {
        m_frames.clear();
        m_animations.clear();
    }

    RectU SpriteSheet::GetFrame(const UInt index)
    {
        if (index < m_frames.size())
        {
            Frame& frame = m_frames[index];
            return { frame.X, frame.Y, frame.Width, frame.Height };
        }

        throw std::out_of_range("Index is Out of Range. Trying to retrieve frame " + index);
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
