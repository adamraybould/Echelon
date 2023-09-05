#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

struct SDL_Window;
struct SDL_Renderer;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

namespace MapleEngine
{
	class ENGINE_API Window
	{
	private:
		SDL_Window* pWindow = nullptr;
		SDL_Renderer* pRenderer = nullptr;

	public:
		~Window();

		bool Create(const char* title);

		void SetTitle(const char* title);

		SDL_Window* GetWindow() { return pWindow; }
		SDL_Renderer* GetRenderer() { return pRenderer; }

	private:
		bool SetIcon();
	};
}