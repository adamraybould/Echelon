#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "Animation.h"
#include "Texture2D.h"
#include "Core/Maths/Rectangle.h"

namespace Graphics
{
    class SpriteSheet : public Texture2D
    {
    private:
        UnorderedMap<String, Animation> m_animations;

        int m_spriteWidth;
        int m_spriteHeight;
        int m_frameCount;

    public:
        SpriteSheet(const SDL_Surface& surface, int frameWidth, int frameHeight, const UnorderedMap<String, Animation>& animations);
        ~SpriteSheet();

        /* Returns the Source Rect of a Sprite within the Sprite Sheet */
        RectF GetSpriteSource(UInt frameIndex) const;

        bool IsAnimationValid(const String& animName) const;
        Animation* GetAnimation(const String& animName);

        int GetFrameWidth() const { return m_spriteWidth; }
        int GetFrameHeight() const { return m_spriteHeight; }
        int GetFrameCount() const { return m_frameCount; }
    };
}

#endif //SPRITESHEET_H
