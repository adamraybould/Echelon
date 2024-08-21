#include "Rendering/Renderer.h"

#include "Utility/Constants.h"

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

    void Renderer::RenderScreen()
    {
        SetViewport();
        SDL_SetRenderDrawColor(&m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(&m_renderer);

    }

    void Renderer::UpdateScreen() const
    {
        SDL_RenderPresent(&m_renderer);
    }

    void Renderer::SetViewport() const
    {
        SDL_Rect viewport = { static_cast<int>(m_pCamera->GetViewport().X), static_cast<int>(m_pCamera->GetViewport().Y), static_cast<int>(m_pCamera->GetViewport().Width), static_cast<int>(m_pCamera->GetViewport().Height) };
        SDL_RenderSetViewport(&m_renderer, &viewport);
        SDL_RenderSetScale(&m_renderer, m_pCamera->GetZoom(), m_pCamera->GetZoom());
    }
}
