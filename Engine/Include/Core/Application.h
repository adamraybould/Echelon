#ifndef APPLICATION_H
#define APPLICATION_H

#include "IProgram.h"
#include "IO/Window.h"
#include "IO/Input.h"
#include "Physics.h"
#include "AssetManager.h"
#include "Scripting/ScriptCore.h"
#include "Scripting/Engine.h"
#include "../Systems/StateSystem.h"
#include "Audio/AudioSystem.h"

namespace Core
{
    namespace Editor { class EngineGUI; }

    class Application final : public IProgram, System
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

        Window& GetWindow() const { return *m_pWindow; }
        Renderer& GetRenderer() const { return m_pWindow->GetRenderer(); }

        StateSystem& GetStateSystem() const { return *m_pStateSystem; }

    private:
        void Initialize();
    };
}

#endif //APPLICATION_H
