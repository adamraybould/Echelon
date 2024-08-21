#ifndef WINDOW_H
#define WINDOW_H

struct SDL_Window;
struct SDL_Renderer;

namespace Core
{
    class Window
    {
    private:
        SDL_Window* m_pWindow = nullptr;
        SDL_Renderer* m_pRenderer = nullptr;

    public:
        ~Window();

        bool Create(const char* title);
        void SetTitle(const char* title);

        SDL_Window& GetWindow() const { return *m_pWindow; }
        SDL_Renderer& GetRenderer() const { return *m_pRenderer; }

    private:
        bool SetIcon();
    };
}

#endif //WINDOW_H
