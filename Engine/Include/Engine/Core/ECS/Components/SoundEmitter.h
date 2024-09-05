#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H
#include "Component.h"

namespace Core
{
    namespace Audio { class AudioBank; class AudioEvent; }

    using namespace Audio;
    namespace Components
    {
        class SoundEmitter : public Component
        {
        private:
            AudioBank* m_pBank = nullptr;

            AudioEvent* m_pAudioEvent_Walk = nullptr;
            AudioEvent* m_pAudioEvent_Run = nullptr;

        public:
            SoundEmitter(Entity& owner);
            void SetupEmbedding(lua_State* L) override;

            void Initialize() override;
            void Destroy() override;

            void PlaySound(const String& name);

            void PlayFootsteps(bool run) const;
            void StopFootsteps() const;
        };
    }
}

#endif //SOUNDEMITTER_H
