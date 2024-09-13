#include "Core/Application.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <GL/glew.h>

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

        Initialise();
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

            //SDL_Delay(16);
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
        m_pInput->Reset();

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

        constexpr UInt titleUpdateIntervalMs = 1000;
        const UInt32 currentTitleUpdateTicks = m_currentTime;

        if (currentTitleUpdateTicks - m_lastTitleUpdateTicks >= titleUpdateIntervalMs * SDL_GetPerformanceFrequency() / 1000)
        {
            const auto openGLVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
            const auto glewVersion = reinterpret_cast<const char*>(glewGetString(GLEW_VERSION));

            const std::string title = "Echelon | FPS: " + std::to_string(FPS) + " | OpenGL Version: " + openGLVersion + " | GLEW Version: " + glewVersion;
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
        m_pEngineGUI->Render();
        m_pWindow->ClearScreen();

        GetRenderer().ProcessRenderQueue();
        m_pPhysics->Render(GetRenderer());

        m_pEngineGUI->RenderImGui(GetRenderer());
        m_pWindow->SwapBuffers();

        /*
        m_pEngineGUI->Render();
        GetRenderer().RenderScreen();

        GetRenderer().ProcessRenderQueue();
        m_pPhysics->Render(GetRenderer());

        m_pEngineGUI->RenderImGui(GetRenderer());

        GetRenderer().PresentScreen();
        */
    }

    void Application::Initialise()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            OutputError("SDL could not Initialize! \nSDL_ERROR: ", "SDL Error", true);
            Exit();
        }

        if (IMG_Init(IMG_INIT_PNG) < 0)
        {
            OutputError("SDL Image could not Initialize! \nSDL_ERROR: ", "SDL Error", true);
            Exit();
        }

        // Setup OpenGL Attributes
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        CreateWindow();
        InitialiseSystems();
    }

    void Application::CreateWindow()
    {
        m_pWindow = std::make_unique<Window>();
        if (!m_pWindow->Create("Echelon"))
        {
            OutputError("Window could not be created! \nSDL_ERROR: ", "SDL Error", true);
            Exit();
        }
    }

    void Application::InitialiseSystems()
    {
        // Initialise Lua Embedding
        m_pScriptCore = std::make_unique<ScriptCore>();
        m_pEngine = std::make_unique<Engine>();

        m_pAssetManager = std::make_unique<AssetManager>(m_pWindow->GetRenderer());
        m_pInput = std::make_unique<Input>();
        m_pAudioSystem = std::make_unique<AudioSystem>();
        m_pPhysics = std::make_unique<Physics>(GetRenderer());

        m_pScriptCore->InitialiseBinders();

        m_pStateSystem = std::make_unique<StateSystem>();
        m_pStateSystem->AddState<States::GameState>(true);

        m_pEngineGUI = std::make_unique<Editor::EngineGUI>(*m_pWindow, *m_pStateSystem, *m_pInput);
    }
}
