#ifndef AUDIOBANK_H
#define AUDIOBANK_H
#include <fmod_studio.h>
#include "Engine/Core/TypeDefs.h"

namespace Core
{
    namespace Audio
    {
        class AudioBank
        {
        private:
            FMOD_STUDIO_SYSTEM& m_system;
            FMOD_STUDIO_BANK* m_pBank;

            const String& m_bankPath;
            bool m_loaded;

        public:
            AudioBank(FMOD_STUDIO_SYSTEM& system, const String& bankPath);
            ~AudioBank();

            bool LoadBank();

        private:
            void Terminate(const FMOD_RESULT& result);
        };
    }
}

#endif //AUDIOBANK_H
