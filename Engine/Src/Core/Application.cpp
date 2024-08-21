#include "Engine/Core/Application.h"
#include "Engine/Rendering/Renderer.h"
#include "Engine/States/GameState.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

namespace Core
{
    Application* Application::m_pInstance;

    Application::Application()
    {
        m_pInstance = this;

        m_pWindow = nullptr;
        m_isRunning = false;

        m_currentTime = SDL_GetPerformanceCounter();
        m_prevTime = 0;
        m_lastTitleUpdateTicks = 0;

        std::srand(static_cast<UInt>(time(nullptr)));

        Initialize();
    }

    void Application::Run()
    {
        m_isRunning = true;
        m_prevTime = SDL_GetTicks();

        // Initialize Systems
        m_pStateSystem->Initialize();

        while (m_isRunning)
        {
            HandleInput();
            Update();
            Render();

            SDL_Delay(16);
        }

        Clean();
    }

    void Application::Clean()
    {
        m_pAssetManager.reset();
        m_pStateSystem.reset();
        m_pInputManager.reset();

        m_pRenderer.reset();
        m_pWindow.reset();

        IMG_Quit();
        SDL_Quit();
    }

    void Application::HandleInput()
    {
        m_pInputManager->Reset();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    {
                        m_isRunning = false;
                        break;
                    }
                default:
                    {
                        break;
                    }
            }

            m_pInputManager->HandleInput(event);
        }
    }

    void Application::Update()
    {
        m_prevTime = m_currentTime;
        m_currentTime = SDL_GetPerformanceCounter();

        float deltaTime = (m_currentTime - m_prevTime) / (float)SDL_GetPerformanceFrequency();
        int FPS = static_cast<int>(1.0f / deltaTime);

        const int titleUpdateIntervalMs = 1000;
        UInt32 currentTitleUpdateTicks = m_currentTime;

        if (currentTitleUpdateTicks - m_lastTitleUpdateTicks >= titleUpdateIntervalMs * SDL_GetPerformanceFrequency() / 1000)
        {
            std::string title = "Echelon | FPS: " + std::to_string(FPS);
            m_pWindow->SetTitle(title.c_str());

            m_lastTitleUpdateTicks = currentTitleUpdateTicks;
        }

        m_pRenderer->Update(deltaTime);
        m_pStateSystem->Update(deltaTime);
    }

    void Application::Render() const
    {
        m_pRenderer->RenderScreen();

        m_pStateSystem->Render(*m_pRenderer);

        m_pRenderer->PresentScreen();
    }

    void Application::DisplayError(const char* error, const char* errorTile, bool displaySDLError)
    {
        std::string errorMessage = std::string(error) + (displaySDLError ? SDL_GetError() : "");
        //MessageBoxA(NULL, errorMessage.c_str(), errorTile, MB_ICONERROR | MB_OK);
    }

    void Application::Initialize()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            DisplayError("SDL could not Initialize! SDL_ERROR:", "SDL Error", true);
            exit(1);
        }
        else
        {
            m_pWindow = std::make_unique<Window>();
            if (!m_pWindow->Create("Echelon"))
            {
                DisplayError("Window could not be created! SDL_ERROR:", "SDL Error", true);
                exit(1);
            }

            m_pRenderer = std::make_unique<Renderer>(m_pWindow->GetRenderer());
        }

        if (IMG_Init(IMG_INIT_PNG | IMG_INIT_PNG) < 0)
        {
            DisplayError("SDL Image could not Initialize! SDL_ERROR:", "SDL Error", true);
            exit(1);
        }

        // Initialize Systems
        m_pAssetManager = std::make_unique<Graphics::AssetManager>(*m_pRenderer);

        m_pStateSystem = std::make_unique<Systems::StateSystem>();
        m_pStateSystem->AddState<States::GameState>(true);

        m_pInputManager = std::make_unique<Systems::InputManager>();
    }
}
