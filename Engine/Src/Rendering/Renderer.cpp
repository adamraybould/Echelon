#include "Rendering/Renderer.h"

namespace Engine::Rendering
{
    Renderer::Renderer(SDL_Renderer& renderer) : m_renderer(renderer)
    {
        m_pCamera = std::make_unique<Camera>();
    }

    void Renderer::Update(float delta) const
    {
        m_pCamera->Update(delta);
    }
}
