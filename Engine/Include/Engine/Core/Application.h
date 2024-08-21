#ifndef APPLICATION_H
#define APPLICATION_H

#include "IProgram.h"
#include "Engine/Graphics/AssetManager.h"
#include "Engine/Systems/StateSystem.h"
#include "Engine/Systems/InputManager.h"
#include "Window.h"
#include "Engine/Utility/Commons.h"

namespace Core
{
    class Application final : public IProgram
    {
    private:
        static Application* m_pInstance;

        UniquePtr<Window> m_pWindow;
        UniquePtr<Renderer> m_pRenderer;
        bool m_isRunning;

        UniquePtr<Graphics::AssetManager> m_pAssetManager;
        UniquePtr<Systems::StateSystem> m_pStateSystem;
        UniquePtr<Systems::InputManager> m_pInputManager;

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
        Renderer& GetRenderer() const { return *m_pRenderer; }

    private:
        void Initialize();
    };
}

#endif //APPLICATION_H
