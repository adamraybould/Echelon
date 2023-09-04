#include "Engine/Main/Window.h"
#include "SDL.h"
#include "SDL_image.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

MapleEngine::Window::~Window()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
}

bool MapleEngine::Window::CreateWindow(const char* title)
{
	pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (pWindow == nullptr)
		return false;

	int rendererFlags = SDL_RENDERER_ACCELERATED;
	pRenderer = SDL_CreateRenderer(pWindow, -1, rendererFlags);
	if (pRenderer == nullptr)
		return false;

	// Set Window Icon
	if (!SetIcon())
		return false;

	return true;
}

void MapleEngine::Window::SetTitle(const char* title)
{
	SDL_SetWindowTitle(pWindow, title);
}

bool MapleEngine::Window::SetIcon()
{
	SDL_Surface* icon = IMG_Load("Icon.png");
	if (icon == nullptr)
		return false;

	SDL_SetWindowIcon(pWindow, icon);
	SDL_FreeSurface(icon);
}
