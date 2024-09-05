#include "Engine/Audio/AudioSystem.h"

#include <iostream>
#include <string>
#include "config.h"
#include "Engine/Audio/AudioBank.h"
#include "Engine/Audio/AudioEvent.h"

namespace Core
{
    namespace Audio
    {
        FMOD_STUDIO_SYSTEM* AudioSystem::m_pSystem;
        UnorderedMap<String, UniquePtr<AudioBank>> AudioSystem::m_pBanks;
        Array<FMOD_STUDIO_EVENTDESCRIPTION*> AudioSystem::m_pEventDescriptions;
        UnorderedMap<String, UniquePtr<AudioEvent>> AudioSystem::m_pEvents;

        AudioSystem::AudioSystem()
        {
            FMOD_RESULT result = FMOD_Studio_System_Create(&m_pSystem, FMOD_VERSION);
            if (result != FMOD_OK)
                Terminate(result);

            result = FMOD_Studio_System_Initialize(m_pSystem, 512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
            if (result != FMOD_OK)
                Terminate(result);

            LoadBank("Audio/Master.bank");
            LoadBank("Audio/Master.strings.bank");

            std::cout << "Audio System Initialised" << std::endl;
        }

        AudioSystem::~AudioSystem()
        {
            for (std::pair<const String, UniquePtr<AudioEvent>>& event : m_pEvents)
            {
                event.second.reset();
            }

            for (UInt i = 0; i < m_pEventDescriptions.size(); i++)
            {
                FMOD_Studio_EventDescription_ReleaseAllInstances(m_pEventDescriptions[i]);
            }

            for (std::pair<const String, UniquePtr<AudioBank>>& bank : m_pBanks)
            {
                bank.second.reset();
            }

            if (m_pSystem != nullptr)
            {
                FMOD_Studio_System_Release(m_pSystem);
            }
        }

        void AudioSystem::Update() const
        {
            FMOD_Studio_System_Update(m_pSystem);
        }

        AudioBank* AudioSystem::LoadBank(const String& path)
        {
            if (!path.empty())
            {
                String assetPath = ASSETS_PATH + path;

                // Return Bank if already created
                if (m_pBanks.contains(assetPath))
                {
                    return m_pBanks[assetPath].get();
                }

                UniquePtr<AudioBank> bank = std::make_unique<AudioBank>(*m_pSystem, assetPath);
                if (bank->LoadBank())
                {
                    m_pBanks.emplace(assetPath, std::move(bank));
                    return m_pBanks[assetPath].get();
                }
            }

            std::cerr << "Failed to Load Audio Bank" << std::endl;
            return nullptr;
        }

        AudioEvent* AudioSystem::LoadEvent(const String& eventPath)
        {
            if (!eventPath.empty())
            {
                if (m_pEvents.contains(eventPath))
                {
                    return m_pEvents[eventPath].get();
                }

                FMOD_STUDIO_EVENTDESCRIPTION* eventDescription = nullptr;
                FMOD_RESULT result = FMOD_Studio_System_GetEvent(m_pSystem, eventPath.c_str(), &eventDescription);
                if (result != FMOD_OK)
                    Terminate(result);

                m_pEventDescriptions.push_back(eventDescription);

                m_pEvents[eventPath] = std::make_unique<AudioEvent>(*m_pEventDescriptions.back());
                return m_pEvents[eventPath].get();
            }

            return nullptr;
        }

        void AudioSystem::Terminate(const FMOD_RESULT& result)
        {
            std::cerr << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
            exit(-1);
        }
    }
}
