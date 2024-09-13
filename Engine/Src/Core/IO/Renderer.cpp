#include "Core/IO/Renderer.h"

#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

#include "Graphics/SpriteMesh.h"
#include "Graphics/Sprite.h"
#include "Rendering/Renderable.h"
#include "Rendering/Shader.h"

using namespace Graphics;
using namespace Rendering;
namespace Core
{
    Array<UniquePtr<Sprite>> Renderer::m_pSprites;
    Map<RenderLayer, Array<Renderable*>> Renderer::m_pRenderQueue;

    Renderer::Renderer(Window& window, SDL_GLContext& context) : m_window(window), m_context(context)
    {
        m_pSpriteMesh = std::make_unique<SpriteMesh>();
        m_pCamera = std::make_unique<Camera>("Camera");
    }

    Renderer::~Renderer()
    {
        for (auto& sprite : m_pSprites)
        {
            sprite.reset();
        }

        m_pSprites.clear();
    }

    void Renderer::Update(const float delta) const
    {
        m_pCamera->Update(delta);
    }

    void Renderer::ProcessRenderQueue()
    {
        for (auto& layer : m_pRenderQueue)
        {
            std::sort(layer.second.begin(), layer.second.end(), [] (Renderable* a, Renderable* b)
            {
                return a->GetDepth() > b->GetDepth();
            });

            for(Renderable* renderable : layer.second)
            {
                if (renderable->IsActive())
                {
                    renderable->Render(*this);
                }
            }
        }
    }

    Sprite& Renderer::CreateSprite(Texture2D& texture)
    {
        m_pSprites.push_back(std::make_unique<Sprite>(texture));
        return *m_pSprites.back();
    }

    void Renderer::AddToRenderQueue(Renderable& renderable)
    {
        m_pRenderQueue[renderable.GetRenderLayer()].push_back(&renderable);
    }

    void Renderer::Render(const Sprite* sprite, const RectF& src, const RectF& dest, const float rotation)
    {
        AttachMesh(sprite, src, dest);

        // Set Uniform Variables
        const Shader& shader = sprite->GetMaterial().GetShader();
        shader.SetUniformMat4("Projection", m_pCamera->GetProjection());
        shader.SetUniformMat4("View", m_pCamera->GetView());
        shader.SetUniformMat4("Transform", CalculateTransformMatrix(dest, rotation));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        DetachMesh(sprite);
    }

    void Renderer::AttachMesh(const Sprite* sprite, const RectF& src, const RectF& dest) const
    {
        if (m_pSpriteMesh != nullptr && sprite != nullptr)
        {
            m_pSpriteMesh->AttachMesh();
            sprite->GetMaterial().Attach();

            UpdateVertices(dest);
            UpdateUVs(src, sprite->GetWidth(), sprite->GetHeight());
        }
    }

    void Renderer::DetachMesh(const Sprite* sprite) const
    {
        if (m_pSpriteMesh != nullptr && sprite != nullptr)
        {
            sprite->GetMaterial().Detach();
            m_pSpriteMesh->DetachMesh();
        }
    }

    void Renderer::UpdateVertices(const RectF& dest) const
    {
        const float width = dest.Width * 0.5f;
        const float height = dest.Height * 0.5f;

        Vector2F vertices[4];
        vertices[0] = Vector2F(width, height);
        vertices[1] = Vector2F(width, -height);
        vertices[2] = Vector2F(-width, -height);
        vertices[3] = Vector2F(-width, height);

        m_pSpriteMesh->UpdateVertexBuffer(vertices);
    }

    void Renderer::UpdateUVs(const RectF& src, const float textureWidth, const float textureHeight) const
    {
        Vector2F uvs[4];
        uvs[0] = Vector2F((src.X + src.Width) / textureWidth, src.Y / textureHeight);
        uvs[1] = Vector2F((src.X + src.Width) / textureWidth, (src.Y + src.Height) / textureHeight);
        uvs[2] = Vector2F(src.X / textureWidth, (src.Y + src.Height) / textureHeight);
        uvs[3] = Vector2F(src.X / textureWidth, src.Y / textureHeight);

        m_pSpriteMesh->UpdateUVBuffer(uvs);
    }

    glm::mat4 Renderer::CalculateTransformMatrix(const RectF& dest, const float rotation) const
    {
        auto transform = glm::mat4(1.0f);
        transform = translate(transform, glm::vec3(dest.X, dest.Y, 0.0f));
        transform = rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = scale(transform, glm::vec3(1.0f, 1.0f, 0.0f));

        return transform;
    }
}
