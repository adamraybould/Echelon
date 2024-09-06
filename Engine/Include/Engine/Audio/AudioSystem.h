#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <fmod_studio.h>
#include <fmod_errors.h>

#include "Engine/Core/System.h"
#include "Engine/Core/TypeDefs.h"

namespace Core
{
    namespace Audio
    {
        class AudioBank;
        class AudioEvent;

        class AudioSystem final : System
        {
        private:
            static FMOD_STUDIO_SYSTEM* m_pSystem;

            static UnorderedMap<String, UniquePtr<AudioBank>> m_pBanks;

            static Array<FMOD_STUDIO_EVENTDESCRIPTION*> m_pEventDescriptions;
            static UnorderedMap<String, UniquePtr<AudioEvent>> m_pEvents;

        public:
            AudioSystem();
            ~AudioSystem();

            static void Update();

            static bool LoadBank(const String& path);
            static UniquePtr<AudioEvent>& LoadEvent(const String& eventPath);

            static bool IsInitialised() { return m_pSystem != nullptr; }

        private:
            static void ReportError(const FMOD_RESULT& result);
        };
    }
}

#endif //AUDIOSYSTEM_H
