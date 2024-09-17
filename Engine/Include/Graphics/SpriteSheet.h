#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "Animation.h"
#include "Texture2D.h"
#include "Core/Maths/Rectangle.h"

namespace Graphics
{
    struct Frame
    {
        UInt X;
        UInt Y;
        UInt Width;
        UInt Height;
    };

    class SpriteSheet : public Texture2D
    {
    private:
        Array<Frame> m_frames;
        UnorderedMap<String, Animation> m_animations;

        int m_spriteWidth;
        int m_spriteHeight;
        int m_frameCount;

    public:
        SpriteSheet(const SDL_Surface& surface, int frameWidth, int frameHeight, const Array<Frame>& frames, const UnorderedMap<String, Animation>& animations);
        ~SpriteSheet();

        /* Returns a Sprite Frame from the Sprite Sheet at a specific index */
        RectU GetFrame(UInt index);

        bool IsAnimationValid(const String& animName) const;
        Animation* GetAnimation(const String& animName);

        int GetFrameWidth() const { return m_spriteWidth; }
        int GetFrameHeight() const { return m_spriteHeight; }
        int GetFrameCount() const { return m_frameCount; }
    };
}

#endif //SPRITESHEET_H
