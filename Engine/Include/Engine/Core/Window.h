#ifndef WINDOW_H
#define WINDOW_H
#include "TypeDefs.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Core
{
    class Renderer;

    class Window
    {
    private:
        SDL_Window* m_pWindow = nullptr;
        UniquePtr<Renderer> m_pRenderer;

    public:
        ~Window();

        bool Create(const char* title);
        void SetTitle(const char* title);

        SDL_Window& GetWindow() const { return *m_pWindow; }
        Renderer& GetRenderer() const { return *m_pRenderer; }

    private:
        bool SetIcon();
    };
}

#endif //WINDOW_H
