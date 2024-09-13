// ReSharper disable CppMemberFunctionMayBeStatic
#include "Core/IO/Window.h"

#include "config.h"
#include "Core/Constants.h"
#include "Core/IO/Renderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>

namespace Core
{
    Window::~Window()
    {
        m_pRenderer.reset();

        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_pWindow);
    }

    bool Window::Create(const char* title)
    {
        m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (m_pWindow == nullptr)
            return false;

        m_context = SDL_GL_CreateContext(m_pWindow);
        if (m_context == nullptr)
        {
            OutputError("Failed to Create OpenGL Context", "OpenGL Error");
            return false;
        }
        SDL_GL_MakeCurrent(m_pWindow, m_context);

        // Initialise GLEW
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            OutputError("Failed to Initialise GLEW", "OpenGL Error");
            return false;
        }

        SDL_GL_SetSwapInterval(1); // Use Vsync

        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_pRenderer = std::make_unique<Renderer>(*this, m_context);

        // Sets Window Icon
        if (!SetIcon())
            return false;

        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        return true;
    }

    void Window::ClearScreen() const
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::SwapBuffers() const
    {
        SDL_GL_SwapWindow(m_pWindow);
    }

    void Window::SetTitle(const char* title) const
    {
        SDL_SetWindowTitle(m_pWindow, title);
    }

    bool Window::SetIcon() const
    {
        const std::string path = std::string(ASSETS_PATH) + "Icon.png";
        SDL_Surface* icon = IMG_Load(path.c_str());
        if (icon == nullptr)
            return false;

        SDL_SetWindowIcon(m_pWindow, icon);
        SDL_FreeSurface(icon);
        return true;
    }
}
