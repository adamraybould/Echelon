#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include "Sprite.h"

namespace Engine::Graphics
{
    class SpriteSheet : public Sprite
    {
    private:
        UInt m_frameWidth;
        UInt m_frameHeight;
        UInt m_frameCount;

    public:
        SpriteSheet(SDL_Texture* texture, UInt frameWidth, UInt frameHeight);
        ~SpriteSheet();

        /* Returns the Source Rect of a Sprite within the Sprite Sheet */
        Rectangle GetSpriteSource(UInt frameIndex) const;

        UInt GetFrameWidth() const { return m_frameWidth; }
        UInt GetFrameHeight() const { return m_frameHeight; }
        UInt GetFrameCount() const { return m_frameCount; }
    };
}

#endif //SPRITESHEET_H
