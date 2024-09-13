#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "Core/Camera.h"
#include "Graphics/Material.h"

namespace Rendering { class IRenderable; }
namespace Graphics { class Sprite; class Texture2D; class SpriteMesh; struct Vector2F4X; }

namespace Core
{
    class Window;

    enum class RenderLayer
    {
        Map,
        Default,
        Player,
        ParticleSystem,
        UI,
    };

    class Renderer
    {
    private:
        Window& m_window;
        SDL_GLContext& m_context;

        static Array<UniquePtr<Graphics::Sprite>> m_pSprites;
        static Map<RenderLayer, Array<Rendering::IRenderable*>> m_pRenderQueue;

        UniquePtr<Graphics::SpriteMesh> m_pSpriteMesh;
        UniquePtr<Camera> m_pCamera;

        UInt m_currentTextureID = 0;
        UInt m_currentShaderID = 0;

    public:
        Renderer(Window& window, SDL_GLContext& context);
        ~Renderer();

        void Update(float delta) const;

        void ProcessRenderQueue();

        static Graphics::Sprite& CreateSprite(Graphics::Texture2D& texture);
        static void AddToRenderQueue(Rendering::IRenderable& renderable);

        //void Render(const Graphics::Texture2D* texture, RectF& src, RectF& dest, float rotation);
        void Render(const Graphics::Sprite* sprite, const RectF& src, const RectF& dest, float rotation);

        Window& GetWindow() const { return m_window; }
        SDL_GLContext& GetContext() const { return m_context; }

        Camera& GetCamera() const { return *m_pCamera; }

    private:
        void AttachMesh(const Graphics::Sprite* sprite, const RectF& src, const RectF& dest);
        void DetachMesh(const Graphics::Sprite* sprite) const;

        void UpdateVertices(const RectF& dest) const;
        void UpdateUVs(const RectF& src, float textureWidth, float textureHeight) const;

        glm::mat4 CalculateTransformMatrix(const RectF& dest, float rotation) const;

        bool IsWithinViewport(const RectF& dest) const;
    };
}

#endif //RENDERER_H
