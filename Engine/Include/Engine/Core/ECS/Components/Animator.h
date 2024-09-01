#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "Component.h"
#include "Engine/Graphics/Animation.h"
#include "Engine/Utility/Delegates.h"

namespace Core
{
    namespace Graphics { class SpriteSheet; struct Animation; }

    using namespace Graphics;
    namespace Components
    {
        class SpriteRenderer;

        class Animator : public Component
        {
        public:
            MultiCastEvent<> OnAnimationPlay;
            MultiCastEvent<> OnAnimationStop;

            MultiCastEvent<> OnAnimationPause;
            MultiCastEvent<> OnAnimationResume;

        private:
            SpriteRenderer* m_pRenderer;
            SpriteSheet* m_pSpriteSheet;

            Animation* m_pCurrentAnimation;
            Frame* m_pCurrentFrame;

            float m_speed = 1.0f;
            bool m_isPlaying = false;
            bool m_isPaused = false;

            int m_frame;
            float m_frameTimer;

        public:
            Animator(Entity& owner);
            void SetupEmbedding(lua_State* L) override;

            void Initialize() override;
            void Update(float delta) override;

            void Play(const String& animName, bool restart = false);
            void Stop();

            void Pause();
            void Resume();

            Animation& GetCurrentAnimation() const { return *m_pCurrentAnimation; }

            void SetPlaybackSpeed(const float value) { m_speed = value; }
            bool IsPlaying() const { return m_isPlaying; }
            bool IsPaused() const { return m_isPaused; }

        private:
            void SetFrame(UInt index);
        };
    }
}

#endif //ANIMATOR_H
