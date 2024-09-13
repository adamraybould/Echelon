#ifndef RENDERABLE_H
#define RENDERABLE_H
#include "Core/Maths/Vector2.h"

namespace Core
{
    class Renderer;
}

namespace Core { enum class RenderLayer; }
namespace Graphics { class Sprite; }
namespace Scene::Components { class Transform; }

namespace Rendering
{
    class Renderable
    {
    private:
        bool m_isActive;
        Core::RenderLayer m_renderLayer;

    public:
        Renderable();

        virtual void Render(Core::Renderer& renderer) = 0;

        bool SetActiveRendering(const bool value) { return m_isActive = value; }
        bool IsActive() const { return m_isActive; }

        void SetRenderLayer(const Core::RenderLayer layer) { m_renderLayer = layer; }
        Core::RenderLayer GetRenderLayer() const { return m_renderLayer; }

        virtual float GetDepth() { return 0.0f; }
    };
}

#endif //RENDERABLE_H
