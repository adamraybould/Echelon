#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

#include "Component.h"
#include "Core/Audio/AudioEvent.h"

namespace Core::Audio { class AudioBank; class AudioEvent; }
using namespace Core::Audio;

namespace Scene
{
    namespace Components
    {
        class SoundEmitter final : public Component
        {
        private:
            UnorderedMap<String, UniquePtr<AudioEvent>> m_audioEvents;

            AudioEvent* m_pAudioEvent_Walk = nullptr;
            AudioEvent* m_pAudioEvent_Run = nullptr;

        public:
            SoundEmitter(Entity& owner);
            void SetupEmbedding(lua_State* L) override;

            void Initialize() override;
            void Destroy() override;

            void PlaySound(const String& soundName, float volume = 1.0f, bool restart = false);
            void StopSound(const String& soundName);
            void StopAllSounds() const;

            void SetVolume(const String& soundName, float volume);
            void SetPitch(const String& soundName, float pitch);

        private:
            AudioEvent* GetSound(const String& soundName);
        };
    }
}

#endif //SOUNDEMITTER_H
