#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

ENGINE_API class SDL_Window;
ENGINE_API class SDL_Renderer;

namespace MapleEngine
{
	ENGINE_API class Window
	{
	private:
		SDL_Window* pWindow = nullptr;
		SDL_Renderer* pRenderer = nullptr;

	public:
		~Window();

		bool CreateWindow(const char* title);

		void SetTitle(const char* title);

		SDL_Window* GetWindow() { return pWindow; }
		SDL_Renderer* GetRenderer() { return pRenderer; }

	private:
		bool SetIcon();
	};
}