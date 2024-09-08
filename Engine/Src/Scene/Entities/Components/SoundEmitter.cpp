#include "Scene/Entities/Components/SoundEmitter.h"
#include "Core/Audio/AudioSystem.h"
#include "Core/Scripting/Prefab.h"

using namespace Core::Audio;
using namespace Core::Scripting;

namespace Scene
{
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
            BindFunction<SoundEmitter>(L, "StopSound", &SoundEmitter::StopSound);
            BindFunction<SoundEmitter>(L, "StopAllSounds", &SoundEmitter::StopAllSounds);

            BindFunction<SoundEmitter>(L, "SetVolume", &SoundEmitter::SetVolume);
            BindFunction<SoundEmitter>(L, "SetPitch", &SoundEmitter::SetPitch);
        }

        void SoundEmitter::Initialize()
        {
            PrefabAsset* audioAsset = GetPrefabAsset(AssetType::AUDIO);
            if (audioAsset != nullptr)
            {
                AudioSystem::LoadBank(audioAsset->GetPath());
                //m_pAudioEvent_Walk = AudioSystem::LoadEvent("event:/PlayerWalk");
                //m_pAudioEvent_Run = AudioSystem::LoadEvent("event:/PlayerRun");
            }
        }

        void SoundEmitter::Destroy()
        {
        }

        void SoundEmitter::PlaySound(const String& soundName, const float volume, const bool restart)
        {
            if (AudioSystem::IsInitialised())
            {
                if (soundName.empty())
                    throw std::invalid_argument("Attempting to Play Sound with empty name");

                // Loads Event if not already
                if (!m_audioEvents.contains(soundName))
                {
                    const UniquePtr<AudioEvent>& audioEvent = AudioSystem::LoadEvent(soundName);
                    m_audioEvents.emplace(soundName, audioEvent.get());
                }

                if (!restart && m_audioEvents[soundName]->IsPlaying())
                    return;

                m_audioEvents[soundName]->SetVolume(volume);
                m_audioEvents[soundName]->Play();
            }
        }

        void SoundEmitter::StopSound(const String& soundName)
        {
            AudioEvent* sound = GetSound(soundName);
            if (sound != nullptr)
            {
                sound->Stop();
            }
        }

        void SoundEmitter::StopAllSounds() const
        {
            for (const auto& sound : m_audioEvents)
            {
                sound.second->Stop();
            }
        }

        void SoundEmitter::SetVolume(const String& soundName, const float volume)
        {
            const AudioEvent* sound = GetSound(soundName);
            if (sound != nullptr)
            {
                sound->SetVolume(volume);
            }
        }

        void SoundEmitter::SetPitch(const String& soundName, const float pitch)
        {
            const AudioEvent* sound = GetSound(soundName);
            if (sound != nullptr)
            {
                sound->SetPitch(pitch);
            }
        }

        AudioEvent* SoundEmitter::GetSound(const String& soundName)
        {
            if (soundName.empty())
                throw std::invalid_argument("Attempting to get Sound with empty name");

            if (!m_audioEvents.contains(soundName))
                return nullptr;

            return m_audioEvents[soundName].get();
        }
    }
}
