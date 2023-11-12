#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "SDL.h"
#include "SDL_image.h"
#include "Engine/Utils/Commons.h"
#include "Window.h"
#include "EngineInterface.h"
#include "Engine/Managers/EngineGUI.h"
#include "Engine/Managers/AssetManager.h"
#include "Engine/Managers/StateManager.h"
#include "Engine/Managers/InputHandler.h"
#include "Engine/States/Level.h"

namespace MapleEngine
{
	class Application : public IApplication
	{
	private:
		static Application* m_rInstance;

		UniquePtr<EngineGUI> m_pEngineGUI;
		UniquePtr<AssetManager> m_pAssetManager;
		UniquePtr<StateManager> m_pStateManager;
		UniquePtr<InputHandler> m_pInputHandler;

		UniquePtr<Window> m_pWindow;
		bool m_isRunning;	

		Uint32 m_currentTime;
		Uint32 m_prevTime;

		float m_lastTitleUpdateTicks;

	public:
		static Application& GetInstance() { return *m_rInstance; }

		Application();

		void Run() override;
		void Clean();

		void HandleInput();
		void Update();
		void Render();

		static void DisplayError(const char* error, const char* errorTile, bool displaySDLError);

		Window& GetWindow() { return *m_pWindow; }
		SDL_Renderer& GetRenderer() { return m_pWindow->GetRenderer(); }

	private:
		/* Initializes the Application, creating the Window and starting the Game Loop.*/
		void Initialize();
	};
}