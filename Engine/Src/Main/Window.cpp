#include "Main/Window.h"
#include <SDL.h>
#include <SDL_image.h>

namespace Engine
{
    Window::~Window()
    {
        SDL_DestroyWindow(m_pWindow);
        SDL_DestroyRenderer(m_pRenderer);
    }

    bool Window::Create(const char* title)
    {
        m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (m_pWindow == nullptr)
            return false;

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

        int rendererFlags = SDL_RENDERER_ACCELERATED;
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, rendererFlags);
        if (m_pRenderer == nullptr)
            return false;

        if (!SetIcon())
            return false;

        return true;
    }

    void Window::SetTitle(const char* title)
    {
        SDL_SetWindowTitle(m_pWindow, title);
    }

    bool Window::SetIcon()
    {
        SDL_Surface* icon = IMG_Load("Icon.png");
        if (icon == nullptr)
            return false;

        SDL_SetWindowIcon(m_pWindow, icon);
        SDL_FreeSurface(icon);
        return true;
    }
}
