#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "Sprite.h"
#include "Animation.h"
#include "Engine/Core/Maths/Rectangle.h"

namespace Core
{
    namespace Graphics
    {
        class SpriteSheet : public Sprite
        {
        private:
            UnorderedMap<String, Animation> m_animations;

            int m_spriteWidth;
            int m_spriteHeight;
            int m_frameCount;

        public:
            SpriteSheet(SDL_Texture* texture, int frameWidth, int frameHeight, UnorderedMap<String, Animation> animations);
            ~SpriteSheet();

            /* Returns the Source Rect of a Sprite within the Sprite Sheet */
            RectI GetSpriteSource(UInt frameIndex) const;

            bool IsAnimationValid(const String& animName) const;
            Animation* GetAnimation(const String& animName);

            int GetFrameWidth() const { return m_spriteWidth; }
            int GetFrameHeight() const { return m_spriteHeight; }
            int GetFrameCount() const { return m_frameCount; }
        };
    }
}

#endif //SPRITESHEET_H
