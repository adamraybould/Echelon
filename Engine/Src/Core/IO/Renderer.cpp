#include "Core/IO/Renderer.h"

namespace Core
{
    Map<RenderLayer, Array<IRenderable*>> Renderer::m_renderQueue;

    Renderer::Renderer(SDL_Renderer& renderer) : m_renderer(renderer)
    {
        m_pCamera = std::make_unique<Camera>("Camera");
    }

    Renderer::~Renderer()
    {
        SDL_DestroyRenderer(&m_renderer);
    }

    void Renderer::Update(float delta) const
    {
        m_pCamera->Update(delta);
    }

    void Renderer::RenderScreen() const
    {
        SetViewport();
        SDL_SetRenderDrawColor(&m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(&m_renderer);
    }

    void Renderer::PresentScreen() const
    {
        SDL_RenderPresent(&m_renderer);
    }

    void Renderer::ResetRenderer() const
    {
        SDL_RenderSetScale(&m_renderer, 1.0f, 1.0f);
        SDL_RenderSetLogicalSize(&m_renderer, 0, 0);
    }

    void Renderer::AddToRenderQueue(IRenderable* renderable, const RenderLayer layer)
    {
        m_renderQueue[layer].push_back(renderable);
    }

    void Renderer::ProcessRenderQueue()
    {
        for (auto& layer : m_renderQueue)
        {
            std::sort(layer.second.begin(), layer.second.end(), [] (IRenderable* a, IRenderable* b)
            {
                return a->GetDepth() < b->GetDepth();
            });

            for(IRenderable* renderable : layer.second)
            {
                renderable->Render(*this);
            }
        }
    }

    void Renderer::SetViewport() const
    {
        SDL_Rect viewport = { static_cast<int>(m_pCamera->GetViewport().X), static_cast<int>(m_pCamera->GetViewport().Y), static_cast<int>(m_pCamera->GetViewport().Width), static_cast<int>(m_pCamera->GetViewport().Height) };
        SDL_RenderSetViewport(&m_renderer, &viewport);
        SDL_RenderSetScale(&m_renderer, m_pCamera->GetZoom(), m_pCamera->GetZoom());
    }
}
