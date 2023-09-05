#include "Engine/Main/Application.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tchar.h>
#include <Windows.h>

MapleEngine::Application* MapleEngine::Application::m_rInstance;

MapleEngine::Application::Application()
{
	m_rInstance = this;

	m_pWindow = nullptr;
	m_isRunning = false;	

	m_currentTime = SDL_GetPerformanceCounter();
	m_prevTime = 0;
	m_lastTitleUpdateTicks = 0;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Initialize Application
	Initialize();
}

void MapleEngine::Application::Run()
{
	m_isRunning = true;
	Uint32 prevTime = SDL_GetTicks();

	while (m_isRunning)
	{
		HandleInput();
		Update();
		Render();

		SDL_Delay(16);
	}

	// Exiting Application
	Clean();
}

void MapleEngine::Application::Clean()
{
	delete m_pAssetManager;
	delete m_pStateManager;

	// Destroy the Window
	delete m_pWindow;

	// Clean Up SDL 
	IMG_Quit();
	SDL_Quit();
}

void MapleEngine::Application::HandleInput()
{
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
	}
}

void MapleEngine::Application::Update()
{
	m_prevTime = m_currentTime;
	m_currentTime = SDL_GetPerformanceCounter();

	float deltaTime = deltaTime = ((m_currentTime - m_prevTime) * 1000 / (float)SDL_GetPerformanceFrequency());
	int FPS = 1000 / deltaTime;

	// Add the FPS to the Window Title with a 1 second delay.
	const int TitleUpdateIntervalMs = 1000;
	Uint32 currentTitleUpdateTicks = m_currentTime;

	if (currentTitleUpdateTicks - m_lastTitleUpdateTicks >= TitleUpdateIntervalMs * SDL_GetPerformanceFrequency() / 1000)
	{
		std::string title = "Echelon | FPS: " + std::to_string(FPS);
		m_pWindow->SetTitle(title.c_str());

		m_lastTitleUpdateTicks = currentTitleUpdateTicks;
	}

	m_pStateManager->UpdateState(deltaTime);
}

void MapleEngine::Application::Render()
{
	SDL_SetRenderDrawColor(m_pWindow->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(m_pWindow->GetRenderer());

	// Render Code
	m_pStateManager->RenderState();

	SDL_RenderPresent(m_pWindow->GetRenderer());
}

void MapleEngine::Application::DisplayError(const char* error, const char* errorTile, bool displaySDLError)
{
	std::string errorMessage = std::string(error) + (displaySDLError ? SDL_GetError() : "");
	MessageBoxA(NULL, errorMessage.c_str(), errorTile, MB_ICONERROR | MB_OK);
}

void MapleEngine::Application::Initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		DisplayError("SDL could not Initialize! SDL_ERROR:", "SDL Error", true);
		exit(1);
	}
	else
	{
		// Create Window with Renderer
		m_pWindow = new Window();
		if (!m_pWindow->Create("Echelon"))
		{
			DisplayError("Window could not be created! SDL_ERROR:", "SDL Error", true);
			exit(1);
		}
	}

	// Initialize SDL Image
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
	{
		DisplayError("SDL Image could not Initialize! SDL_ERROR:", "SDL Error", true);
		exit(1);
	}

	// Initialize Managers
	m_pAssetManager = new MapleEngine::AssetManager(*m_pWindow->GetRenderer());
	m_pStateManager = new MapleEngine::StateManager();
}