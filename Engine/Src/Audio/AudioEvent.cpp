#include "Engine/Audio/AudioEvent.h"

#include <iostream>

namespace Core
{
    namespace Audio
    {
        AudioEvent::AudioEvent(FMOD_STUDIO_EVENTDESCRIPTION& description) : m_pDescription(description)
        {
            CreateInstance();

            m_isPlaying = false;
        }

        AudioEvent::~AudioEvent()
        {
            FMOD_Studio_EventInstance_Release(m_pInstance);
        }

        void AudioEvent::Play()
        {
            if (m_isLoaded && m_pInstance != nullptr)
            {
                FMOD_Studio_EventInstance_Start(m_pInstance);
                m_isPlaying = true;
            }
        }

        void AudioEvent::Stop(const FMOD_STUDIO_STOP_MODE mode)
        {
            if (m_isLoaded && m_pInstance != nullptr)
            {
                FMOD_Studio_EventInstance_Stop(m_pInstance, mode);
                m_isPlaying = false;
            }
        }

        void AudioEvent::CreateInstance()
        {
            FMOD_RESULT result = FMOD_Studio_EventDescription_CreateInstance(&m_pDescription, &m_pInstance);
            if (result != FMOD_OK)
            {
                std::cerr << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
                m_isLoaded = false;
            }
            else
            {
                m_isLoaded = true;
            }
        }
    }
}
