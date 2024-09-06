#include "Core/IO/Window.h"
#include "Core/Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Core/IO/Renderer.h"
#include "config.h"

namespace Core
{
    Window::~Window()
    {
        SDL_DestroyWindow(m_pWindow);
        m_pRenderer.reset();
    }

    bool Window::Create(const char* title)
    {
        m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (m_pWindow == nullptr)
            return false;

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

        int rendererFlags = SDL_RENDERER_ACCELERATED;
        SDL_Renderer* renderer = SDL_CreateRenderer(m_pWindow, -1, rendererFlags);
        if (renderer == nullptr)
            return false;

        m_pRenderer = std::make_unique<Renderer>(*renderer);

        SDL_RenderSetIntegerScale(*m_pRenderer, SDL_TRUE);

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
        std::string path = std::string(ASSETS_PATH) + "Icon.png";
        SDL_Surface* icon = IMG_Load(path.c_str());
        if (icon == nullptr)
            return false;

        SDL_SetWindowIcon(m_pWindow, icon);
        SDL_FreeSurface(icon);
        return true;
    }
}
