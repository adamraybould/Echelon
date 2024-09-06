#include "Core/Application.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <windows.h>

#include "Core/IO/Renderer.h"
#include "States/GameState.h"
#include "Editor/EngineGUI.h"

namespace Core
{
    using namespace Audio;
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

        //m_pScriptCore->SetupBindings();

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
        m_pScriptCore.reset();
        m_pEngine.reset();
        m_pPhysics.reset();
        m_pAudioSystem.reset();

        m_pEngineGUI.reset();
        m_pAssetManager.reset();
        m_pStateSystem.reset();
        m_pInput.reset();

        m_pWindow.reset();

        IMG_Quit();
        SDL_Quit();
    }

    void Application::HandleInput()
    {
        m_pInput.reset();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            m_pEngineGUI->HandleInput(event);
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

            m_pInput->ProcessInput(event);
            m_pInput->ProcessMouseInput(event);
        }
    }

    void Application::Update()
    {
        m_prevTime = m_currentTime;
        m_currentTime = SDL_GetPerformanceCounter();

        const float deltaTime = (m_currentTime - m_prevTime) / static_cast<float>(SDL_GetPerformanceFrequency());
        const int FPS = static_cast<int>((1.0f / deltaTime) + 0.5f);

        const UInt titleUpdateIntervalMs = 1000;
        UInt32 currentTitleUpdateTicks = m_currentTime;

        if (currentTitleUpdateTicks - m_lastTitleUpdateTicks >= titleUpdateIntervalMs * SDL_GetPerformanceFrequency() / 1000)
        {
            std::string title = "Echelon | FPS: " + std::to_string(FPS);
            m_pWindow->SetTitle(title.c_str());

            m_lastTitleUpdateTicks = currentTitleUpdateTicks;
        }

        m_pPhysics->Update();
        AudioSystem::Update();

        GetRenderer().Update(deltaTime);
        m_pEngineGUI->Update(deltaTime);
        m_pStateSystem->Update(deltaTime);
        m_pScriptCore->Update(deltaTime);
    }

    void Application::Render() const
    {
        m_pEngineGUI->Render(GetRenderer());
        GetRenderer().RenderScreen();

        GetRenderer().ProcessRenderQueue();
        m_pPhysics->Render(GetRenderer());

        m_pEngineGUI->RenderImGui(GetRenderer());

        GetRenderer().PresentScreen();
    }

    void Application::Initialize()
    {
        // Initialise Lua Embedding
        m_pScriptCore = std::make_unique<ScriptCore>();
        m_pEngine = std::make_unique<Engine>();

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            OutputError("SDL could not Initialize! SDL_ERROR:", "SDL Error", true, true);

        // Only runs if SDL is initialised
        m_pWindow = std::make_unique<Window>();
        if (!m_pWindow->Create("Echelon"))
            OutputError("Window could not be created! SDL_ERROR:", "SDL Error", true, true);

        if (IMG_Init(IMG_INIT_PNG) < 0)
            OutputError("SDL Image could not Initialize! SDL_ERROR:", "SDL Error", true, true);


        // Initialise Systems
        m_pPhysics = std::make_unique<Physics>(GetRenderer());

        m_pAssetManager = std::make_unique<Graphics::AssetManager>(m_pWindow->GetRenderer());
        m_pAudioSystem = std::make_unique<Audio::AudioSystem>();

        m_pInput = std::make_unique<Input>();

        m_pScriptCore->InitialiseBinders();

        m_pStateSystem = std::make_unique<StateSystem>();
        m_pStateSystem->AddState<States::GameState>(true);

        m_pEngineGUI = std::make_unique<Editor::EngineGUI>(*m_pWindow, *m_pStateSystem, *m_pInput);
    }
}
