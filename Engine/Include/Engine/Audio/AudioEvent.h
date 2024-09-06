#ifndef AUDIOEVENT_H
#define AUDIOEVENT_H

#include <fmod_studio.h>
#include <fmod_errors.h>
#include "Engine/Core/TypeDefs.h"

namespace Core
{
    namespace Audio
    {
        class AudioEvent
        {
        private:
            FMOD_STUDIO_EVENTDESCRIPTION& m_pDescription;
            FMOD_STUDIO_EVENTINSTANCE* m_pInstance = nullptr;

            bool m_isLoaded = false;
            bool m_isPlaying = false;

        public:
            AudioEvent(FMOD_STUDIO_EVENTDESCRIPTION& description);
            ~AudioEvent();

            void Play();
            void Stop(FMOD_STUDIO_STOP_MODE mode = FMOD_STUDIO_STOP_ALLOWFADEOUT);

            void SetVolume(float volume) const;
            void SetPitch(float pitch) const;

            bool IsPlaying() const { return m_isPlaying; }

        private:
            void CreateInstance();
            bool IsLoaded() const { return m_isLoaded && m_pInstance != nullptr; }
        };
    }
}

#endif //AUDIOEVENT_H
