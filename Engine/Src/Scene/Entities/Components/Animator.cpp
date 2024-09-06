#include "Scene/Entities/Components/Animator.h"

#include "Scene/Entities/Entity.h"
#include "Graphics/SpriteSheet.h"
#include "Scene/Entities/Components/SpriteRenderer.h"

namespace Scene
{
    namespace Components
    {
        Animator::Animator(Entity& owner) : Component(owner)
        {
            m_pRenderer = nullptr;
            m_pSpriteSheet = nullptr;
            m_pCurrentAnimation = nullptr;
            m_pCurrentFrame = nullptr;

            m_speed = 1.0f;

            m_frame = 0;
            m_frameTimer = 0.0f;
        }

        void Animator::SetupEmbedding(lua_State* L)
        {
            Component::SetupEmbedding(L);

            BindClass<Animator>(L);
            BindFunction<Animator>(L, "PlayAnimation", &Animator::PlayAnimation);
            BindFunction<Animator>(L, "Stop", &Animator::Stop);

            BindFunction<Animator>(L, "Pause", &Animator::Pause);
            BindFunction<Animator>(L, "Resume", &Animator::Resume);

            BindFunction<Animator>(L, "IsCurrentAnimation", &Animator::IsCurrentAnimation);

            BindFunction<Animator>(L, "SetPlaybackSpeed", &Animator::SetPlaybackSpeed);
            BindFunction<Animator>(L, "IsPlaying", &Animator::IsPlaying);
            BindFunction<Animator>(L, "IsPaused", &Animator::IsPaused);
        }

        void Animator::Initialize()
        {
            m_pRenderer = GetOwner().GetComponent<SpriteRenderer>();
            m_pSpriteSheet = static_cast<SpriteSheet*>(&m_pRenderer->GetSprite());

            if (!m_initialAnimName.empty())
            {
                PlayAnimation(m_initialAnimName);
            }
        }

        void Animator::Update(const float delta)
        {
            if (m_pCurrentAnimation == nullptr || m_pCurrentFrame == nullptr || m_pRenderer == nullptr)
                return;

            if (m_isPaused || !m_isPlaying)
                return;

            m_frameTimer += delta;
            float frameDuration = m_pCurrentFrame->Duration * 0.001f; // Convert milliseconds to seconds
            if (m_frameTimer >= frameDuration * m_speed)
            {
                m_frame++;

                // Loop back to start
                if (m_pCurrentAnimation->Looping && m_frame >= m_pCurrentAnimation->GetFrameLength())
                    m_frame = 0;

                SetFrame(m_frame);
                m_frameTimer = 0.0f;
            }
        }

        void Animator::PlayAnimation(const String& animName, const bool restart)
        {
            // Encase called before Sprite Sheet is set, store the animation to play when Initialised
            if (m_pSpriteSheet == nullptr)
            {
                m_initialAnimName = animName;
                return;
            }

            if (!restart)
            {
                if (m_pCurrentAnimation != nullptr && animName == m_pCurrentAnimation->Name)
                    return;
            }

            if (m_pSpriteSheet != nullptr && m_pSpriteSheet->IsAnimationValid(animName))
            {
                Stop();
                m_pCurrentAnimation = m_pSpriteSheet->GetAnimation(animName);
                SetFrame(m_frame);

                m_isPlaying = true;
                OnAnimationPlay.Broadcast();
                return;
            }

            std::cerr << "Attempting to play Invalid Animation '" << animName << "'" << std::endl;
        }

        void Animator::Stop()
        {
            m_frame = 0;
            m_frameTimer = 0.0f;

            m_isPlaying = false;
            OnAnimationStop.Broadcast();
        }

        void Animator::Pause()
        {
            m_isPaused = true;
            OnAnimationPause.Broadcast();
        }

        void Animator::Resume()
        {
            m_isPaused = false;
            OnAnimationResume.Broadcast();
        }

        bool Animator::IsCurrentAnimation(const String& animName) const
        {
            if (m_pCurrentAnimation != nullptr)
            {
                if (m_pCurrentAnimation->Name == animName)
                    return true;
            }

            return false;
        }

        void Animator::SetFrame(const UInt index)
        {
            if (m_pCurrentAnimation != nullptr)
            {
                m_pCurrentFrame = &m_pCurrentAnimation->Frames[index];
                m_pRenderer->SetDisplaySource(m_pCurrentFrame->X, m_pCurrentFrame->Y, m_pCurrentFrame->Width, m_pCurrentFrame->Height);
            }
        }
    }
}
