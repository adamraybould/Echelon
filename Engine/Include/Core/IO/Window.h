#ifndef WINDOW_H
#define WINDOW_H

#include <memory>

#include "Core/System.h"
#include <SDL2/SDL_video.h>

struct SDL_Window;
struct SDL_Renderer;

namespace Core
{
    class Renderer;

    class Window final : System
    {
    private:
        SDL_Window* m_pWindow = nullptr;
        SDL_GLContext m_context = nullptr;
        std::unique_ptr<Renderer> m_pRenderer;

    public:
        ~Window() override;

        bool Create(const char* title);

        void ClearScreen();
        void SwapBuffers() const;

        void SetTitle(const char* title) const;

        SDL_Window& GetWindow() const { return *m_pWindow; }
        SDL_GLContext& GetContext() { return m_context; }
        Renderer& GetRenderer() const { return *m_pRenderer; }

    private:
        bool SetIcon() const;
    };
}

#endif //WINDOW_H
