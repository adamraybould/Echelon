#include "Engine/Core/ECS/Components/SoundEmitter.h"

#include "Engine/Audio/AudioEvent.h"
#include "Engine/Audio/AudioSystem.h"
#include "Engine/Core/Scripting/Prefab.h"

namespace Core
{
    using namespace Audio;
    namespace Components
    {
        SoundEmitter::SoundEmitter(Entity& owner) : Component(owner)
        {

        }

        void SoundEmitter::SetupEmbedding(lua_State* L)
        {
            Component::SetupEmbedding(L);

            BindClass<SoundEmitter>(L);
            BindFunction<SoundEmitter>(L, "PlaySound", &SoundEmitter::PlaySound);

            BindFunction<SoundEmitter>(L, "PlayFootsteps", &SoundEmitter::PlayFootsteps);
            BindFunction<SoundEmitter>(L, "StopFootsteps", &SoundEmitter::StopFootsteps);
        }

        void SoundEmitter::Initialize()
        {
            PrefabAsset* audioAsset = GetPrefabAsset(AssetType::AUDIO);
            if (audioAsset != nullptr)
            {
                AudioSystem::LoadBank(audioAsset->GetPath());
                m_pAudioEvent_Walk = AudioSystem::LoadEvent("event:/PlayerWalk");
                m_pAudioEvent_Run = AudioSystem::LoadEvent("event:/PlayerRun");
            }
        }

        void SoundEmitter::Destroy()
        {
            m_pBank = nullptr;
        }

        void SoundEmitter::PlaySound(const ::String& name)
        {

        }

        void SoundEmitter::PlayFootsteps(const bool run) const
        {
            if (run)
            {
                if (m_pAudioEvent_Run != nullptr)
                {
                    if (!m_pAudioEvent_Run->IsPlaying())
                    {
                        m_pAudioEvent_Walk->Stop();
                        m_pAudioEvent_Run->Play();
                    }
                }
            }
            else
            {
                if (m_pAudioEvent_Walk != nullptr)
                {
                    if (!m_pAudioEvent_Walk->IsPlaying())
                    {
                        m_pAudioEvent_Run->Stop();
                        m_pAudioEvent_Walk->Play();
                    }
                }
            }
        }

        void SoundEmitter::StopFootsteps() const
        {
            if (m_pAudioEvent_Walk != nullptr)
            {
                if (m_pAudioEvent_Walk->IsPlaying())
                {
                    m_pAudioEvent_Walk->Stop();
                }
            }

            if (m_pAudioEvent_Run != nullptr)
            {
                if (m_pAudioEvent_Run->IsPlaying())
                {
                    m_pAudioEvent_Run->Stop();
                }
            }
        }
    }
}
