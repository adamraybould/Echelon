#ifndef APPLICATION_H
#define APPLICATION_H

#include "IProgram.h"
#include "Scripting/ScriptCore.h"
#include "Engine/Graphics/AssetManager.h"
#include "Engine/Core/Systems/StateSystem.h"
#include "Engine/Core/Systems/InputManager.h"
#include "Window.h"
#include "Engine/Utility/Commons.h"

namespace Core
{
    namespace Editor { class EngineGUI; }

    class Application final : public IProgram
    {
    private:
        static Application* m_pInstance;

        UniquePtr<Window> m_pWindow;
        bool m_isRunning;

        UniquePtr<ScriptCore> m_pScriptCore;

        UniquePtr<Editor::EngineGUI> m_pEngineGUI;
        UniquePtr<Graphics::AssetManager> m_pAssetManager;
        UniquePtr<Systems::InputManager> m_pInputManager;
        UniquePtr<Systems::StateSystem> m_pStateSystem;

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
