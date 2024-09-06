#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

#include "Core/Camera.h"
#include "IRenderable.h"

namespace Core
{
    enum class RenderLayer
    {
        Map,
        Default,
        Player,
        UI,
    };

    class Renderer
    {
    private:
        SDL_Renderer& m_renderer;
        UniquePtr<Camera> m_pCamera;

        static Map<RenderLayer, Array<IRenderable*>> m_renderQueue;

    public:
        Renderer(SDL_Renderer& renderer);
        ~Renderer();

        void Update(float delta) const;

        void RenderScreen() const;
        void PresentScreen() const;
        void ResetRenderer() const;

        static void AddToRenderQueue(IRenderable* renderable, RenderLayer layer);
        void ProcessRenderQueue();

        Camera& GetCamera() const { return *m_pCamera; }
        operator SDL_Renderer*() const { return &m_renderer; }

    private:
        void SetViewport() const;
    };
}

#endif //RENDERER_H
