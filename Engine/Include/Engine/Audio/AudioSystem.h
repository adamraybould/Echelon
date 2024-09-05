#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <fmod_studio.h>
#include <fmod_errors.h>
#include "Engine/Core/TypeDefs.h"
#include "Engine/Core/Scripting/ScriptCore.h"

namespace Core
{
    namespace Audio
    {
        class AudioBank;
        class AudioEvent;

        class AudioSystem
        {
        private:
            static FMOD_STUDIO_SYSTEM* m_pSystem;

            static UnorderedMap<String, UniquePtr<AudioBank>> m_pBanks;

            static Array<FMOD_STUDIO_EVENTDESCRIPTION*> m_pEventDescriptions;
            static UnorderedMap<String, UniquePtr<AudioEvent>> m_pEvents;

        public:
            AudioSystem();
            ~AudioSystem();

            void Update() const;

            static AudioBank* LoadBank(const String& path);
            static AudioEvent* LoadEvent(const String& eventPath);

        private:
            static void Terminate(const FMOD_RESULT& result);
        };
    }
}

#endif //AUDIOSYSTEM_H
