#include "Engine/Main/Application.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

MapleEngine::Application* MapleEngine::Application::m_rInstance;

MapleEngine::Application::Application()
{
	m_rInstance = this;

	m_pWindow = nullptr;
	m_isRunning = false;

	m_pStateManager = new MapleEngine::StateManager();

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
	delete m_pStateManager;

	// Destroy the Window
	delete m_pWindow;

	// Quit SDL
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

void MapleEngine::Application::Initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not Initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	else
	{
		// Create Window with Renderer
		m_pWindow = new Window();
		if (!m_pWindow->CreateWindow("Echelon"))
		{
			printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
			exit(1);
		}
	}
}