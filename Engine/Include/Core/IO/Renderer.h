#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>

#include "Core/Camera.h"
#include "IRenderable.h"

namespace Graphics { class Texture2D; }

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

        void RenderTexture(const Graphics::Texture2D& texture, SDL_Rect src, SDL_Rect dest, float rotation = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

        Camera& GetCamera() const { return *m_pCamera; }
        operator SDL_Renderer*() const { return &m_renderer; }

    private:
        void SetViewport() const;
    };
}

#endif //RENDERER_H
