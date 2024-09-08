#include "Core/Audio/AudioSystem.h"

#include <iostream>
#include <string>
#include "config.h"
#include "Core/Audio/AudioBank.h"
#include "Core/Audio/AudioEvent.h"

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
                ReportError(result);

            result = FMOD_Studio_System_Initialize(m_pSystem, 512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
            if (result != FMOD_OK)
                ReportError(result);

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

        void AudioSystem::Update()
        {
            FMOD_Studio_System_Update(m_pSystem);
        }

        bool AudioSystem::LoadBank(const String& path)
        {
            if (path.empty())
            {
                PrintErrorMessage("Audio System Error: Audio Bank Path is Empty");
                return false;
            }

            String assetPath = ASSETS_PATH + path;
            if (m_pBanks.contains(assetPath))
            {
                //PrintErrorMessage("Trying to Load Bank that has already been loaded '" + assetPath + "'");
                return true;
            }

            UniquePtr<AudioBank> bank = std::make_unique<AudioBank>(*m_pSystem, assetPath);
            if (bank->LoadBank())
            {
                m_pBanks.emplace(assetPath, std::move(bank));
                return true;
            }

            OutputError("Failed to Load Audio Bank '" + assetPath + "'", "Audio System Error", false);
            return false;
        }

        UniquePtr<AudioEvent>& AudioSystem::LoadEvent(const String& eventPath)
        {
            if (eventPath.empty())
            {
                PrintErrorMessage("Audio System Error: Audio Event Path is Empty");
                throw std::invalid_argument("Audio System Error: Audio Event Path is Empty");
            }

            if (m_pEvents.contains(eventPath))
                return m_pEvents[eventPath];


            const String path = "event:/" + eventPath;
            FMOD_STUDIO_EVENTDESCRIPTION* eventDescription = nullptr;
            const FMOD_RESULT result = FMOD_Studio_System_GetEvent(m_pSystem, path.c_str(), &eventDescription);
            if (result != FMOD_OK)
                ReportError(result);

            m_pEventDescriptions.push_back(eventDescription);
            m_pEvents[eventPath] = std::make_unique<AudioEvent>(*m_pEventDescriptions.back());

            return m_pEvents[eventPath];
        }

        void AudioSystem::ReportError(const FMOD_RESULT& result)
        {
            OutputError(FMOD_ErrorString(result), "FMOD Error", true);
        }
    }
}
