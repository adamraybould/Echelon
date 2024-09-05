#ifndef APPLICATION_H
#define APPLICATION_H

#include "Engine.h"
#include "Input.h"
#include "Physics.h"
#include "Interfaces/IProgram.h"
#include "Scripting/ScriptCore.h"
#include "Engine/Graphics/AssetManager.h"
#include "Engine/Core/Systems/StateSystem.h"
#include "Window.h"
#include "Engine/Utility/Commons.h"
#include "Engine/Audio/AudioSystem.h"

namespace Core
{
    namespace Editor { class EngineGUI; }

    class Application final : public IProgram
    {
    private:
        static Application* m_pInstance;

        UniquePtr<Window> m_pWindow;
        bool m_isRunning;

        // Systems
        UniquePtr<Engine> m_pEngine;
        UniquePtr<ScriptCore> m_pScriptCore;
        UniquePtr<Editor::EngineGUI> m_pEngineGUI;
        UniquePtr<Graphics::AssetManager> m_pAssetManager;

        UniquePtr<Input> m_pInput;
        UniquePtr<Physics> m_pPhysics;
        UniquePtr<StateSystem> m_pStateSystem;
        UniquePtr<Audio::AudioSystem> m_pAudioSystem;

        UInt32 m_currentTime;
        UInt32 m_prevTime;
        float m_lastTitleUpdateTicks;

    public:
        static Application& GetInstance() { return *m_pInstance; }

        Application();

        void Run() override;
        void Clean();

        void HandleInput();
        void Update();
        void Render() const;

        static void DisplayError(const char* error, const char* errorTile, bool displaySDLError);

        Window& GetWindow() const { return *m_pWindow; }
        Renderer& GetRenderer() const { return m_pWindow->GetRenderer(); }

        Systems::StateSystem& GetStateSystem() const { return *m_pStateSystem; }

    private:
        void Initialize();
    };
}

#endif //APPLICATION_H
