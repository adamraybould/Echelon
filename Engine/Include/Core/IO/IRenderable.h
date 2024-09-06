#ifndef IRENDERABLE_H
#define IRENDERABLE_H

namespace Core
{
    enum class RenderLayer;
    class Renderer;

    class IRenderable
    {
    private:
        RenderLayer m_renderLayer;

    public:
        IRenderable() = default;
        virtual ~IRenderable() = default;
        virtual void Render(Renderer& renderer) = 0;

        void SetRenderLayer(const RenderLayer layer) { m_renderLayer = layer; }
        RenderLayer GetRenderLayer() const { return m_renderLayer; }

        virtual float GetDepth() { return 0.0f; }
    };
}

#endif //IRENDERABLE_H
