#include "Core/Audio/AudioBank.h"
#include <fmod_errors.h>
#include <iostream>

namespace Core
{
    namespace Audio
    {
        AudioBank::AudioBank(FMOD_STUDIO_SYSTEM& system, const String& bankPath) : m_system(system), m_bankPath(bankPath)
        {
            m_loaded = false;
        }

        AudioBank::~AudioBank()
        {
            if (m_pBank != nullptr)
            {
                FMOD_Studio_Bank_Unload(m_pBank);
            }
        }

        bool AudioBank::LoadBank()
        {
            if (!m_loaded)
            {
                if (!m_bankPath.empty())
                {
                    FMOD_RESULT result = FMOD_Studio_System_LoadBankFile(&m_system, m_bankPath.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &m_pBank);
                    if (result == FMOD_OK)
                    {
                        m_loaded = true;
                        return true;
                    }
                    else
                    {
                        Terminate(result);
                        return false;
                    }
                }
            }

            return true;
        }

        void AudioBank::Terminate(const FMOD_RESULT& result)
        {
            std::cerr << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
            exit(-1);
        }
    }
}
