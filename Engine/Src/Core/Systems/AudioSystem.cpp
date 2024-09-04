#include "Engine/Core/Systems/AudioSystem.h"
#include <iostream>


namespace Core
{
    namespace Systems
    {
        AudioSystem::AudioSystem()
        {
            FMOD_SYSTEM* system;
            FMOD_RESULT result = FMOD_System_Create(&system, FMOD_VERSION);

            /*
            m_pAudioDevice = alcOpenDevice(nullptr);
            if (m_pAudioDevice == nullptr)
            {
                std::cerr << "Failed to open Audio Device" << std::endl;
                exit(-1);
            }

            m_pContext = alcCreateContext(m_pAudioDevice, nullptr);
            if (m_pContext == nullptr || alcMakeContextCurrent(m_pContext) == ALC_FALSE)
            {
                std::cerr << "Failed to Create or Make Current OpenAL Context." << std::endl;
                if (m_pContext != nullptr)
                {
                    alcDestroyContext(m_pContext);
                }

                alcCloseDevice(m_pAudioDevice);
                exit(-1);
            }

            */
            std::cout << "Audio System Initialised" << std::endl;
        }

        AudioSystem::~AudioSystem()
        {
            //alcMakeContextCurrent(nullptr);
            //alcDestroyContext(m_pContext);
            //alcCloseDevice(m_pAudioDevice);
        }

        void AudioSystem::Update()
        {
            //m_pSystem->update();
        }
    }
}
