#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include "Sprite.h"
#include "Animation.h"

namespace Core
{
    namespace Graphics
    {
        class SpriteSheet : public Sprite
        {
        private:
            UnorderedMap<String, Animation> m_animations;

            UInt m_spriteWidth;
            UInt m_spriteHeight;
            UInt m_frameCount;

        public:
            SpriteSheet(SDL_Texture* texture, UInt frameWidth, UInt frameHeight, UnorderedMap<String, Animation> animations);
            ~SpriteSheet();

            /* Returns the Source Rect of a Sprite within the Sprite Sheet */
            Rectangle GetSpriteSource(UInt frameIndex) const;

            bool IsAnimationValid(const String& animName) const;
            Animation* GetAnimation(const String& animName);

            UInt GetFrameWidth() const { return m_spriteWidth; }
            UInt GetFrameHeight() const { return m_spriteHeight; }
            UInt GetFrameCount() const { return m_frameCount; }
        };
    }
}

#endif //SPRITESHEET_H
