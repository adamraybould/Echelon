#include "Core/Audio/AudioEvent.h"

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
            if (IsLoaded())
            {
                FMOD_Studio_EventInstance_Start(m_pInstance);
                m_isPlaying = true;
            }
        }

        void AudioEvent::Stop(const FMOD_STUDIO_STOP_MODE mode)
        {
            if (IsLoaded())
            {
                FMOD_Studio_EventInstance_Stop(m_pInstance, mode);
                m_isPlaying = false;
            }
        }

        void AudioEvent::SetVolume(const float volume) const
        {
            if (IsLoaded())
            {
                FMOD_Studio_EventInstance_SetVolume(m_pInstance, volume);
            }
        }

        void AudioEvent::SetPitch(const float pitch) const
        {
            if (IsLoaded())
            {
                FMOD_Studio_EventInstance_SetPitch(m_pInstance, pitch);
            }
        }

        void AudioEvent::CreateInstance()
        {
            const FMOD_RESULT result = FMOD_Studio_EventDescription_CreateInstance(&m_pDescription, &m_pInstance);
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
