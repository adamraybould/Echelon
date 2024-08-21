#ifndef RENDERER_H
#define RENDERER_H
#include <SDL.h>
#include "Camera.h"
#include "Utility/Commons.h"

namespace Engine::Rendering
{
    class Renderer
    {
    private:
        SDL_Renderer& m_renderer;
        
        UniquePtr<Camera> m_pCamera;

    public:
        Renderer(SDL_Renderer& renderer);
        ~Renderer() = default;

        void Update(float delta) const;

        void RenderScreen() const;
        void PresentScreen() const;

        Camera& GetCamera() const { return *m_pCamera; }
        operator SDL_Renderer*() const { return &m_renderer; }

    private:
        void SetViewport() const;
    };
}

#endif //RENDERER_H
