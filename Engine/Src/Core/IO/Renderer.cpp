#include "Core/IO/Renderer.h"

#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

#include "Rendering/LightManager.h"
#include "Graphics/Material.h"
#include "Graphics/SpriteMesh.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture2D.h"
#include "Rendering/IRenderable.h"
#include "Rendering/Shader.h"

using namespace Graphics;
using namespace Rendering;
namespace Core
{
    Array<UniquePtr<Sprite>> Renderer::m_pSprites;
    Map<RenderLayer, Array<IRenderable*>> Renderer::m_pRenderQueue;

    Renderer::Renderer(Window& window, SDL_GLContext& context) : m_window(window), m_context(context)
    {
        m_pLightManager = std::make_unique<LightManager>();

        m_pSpriteMesh = std::make_unique<SpriteMesh>();
        m_pCamera = std::make_unique<Camera>("Camera");
    }

    Renderer::~Renderer()
    {
        if (m_pLightManager != nullptr)
            m_pLightManager.reset();

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
        m_pSpriteMesh->AttachMesh();

        for (auto& layer : m_pRenderQueue)
        {
            std::sort(layer.second.begin(), layer.second.end(), [] (IRenderable* a, IRenderable* b)
            {
                return a->GetDepth() > b->GetDepth();
            });

            for(IRenderable* renderable : layer.second)
            {
                if (renderable->IsActive())
                {
                    renderable->Render(*this);
                }
            }
        }

        m_pSpriteMesh->DetachMesh();

        m_currentTextureID = 0;
        m_currentShaderID = 0;
    }

    Sprite& Renderer::CreateSprite(Texture2D& texture)
    {
        m_pSprites.push_back(std::make_unique<Sprite>(texture));
        return *m_pSprites.back();
    }

    void Renderer::AddToRenderQueue(IRenderable& renderable)
    {
        m_pRenderQueue[renderable.GetRenderLayer()].push_back(&renderable);
    }

    void Renderer::Render(const Sprite* sprite, const RectF& src, const RectF& dest, const float rotation)
    {
        if (IsWithinViewport(dest))
        {
            AttachMesh(sprite, src, dest);

            // Set Uniform Variables
            const Shader& shader = sprite->GetMaterial().GetShader();
            shader.SetUniformMat4("Projection", m_pCamera->GetProjection());
            shader.SetUniformMat4("View", m_pCamera->GetView());
            shader.SetUniformMat4("Transform", CalculateTransformMatrix(dest, rotation));

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }
    }

    void Renderer::AttachMesh(const Sprite* sprite, const RectF& src, const RectF& dest)
    {
        if (m_pSpriteMesh != nullptr && sprite != nullptr)
        {
            const UInt shaderID = sprite->GetMaterial().GetShader().GetID();
            const UInt textureID = sprite->GetMaterial().GetTexture().GetTextureID();

            if (m_currentShaderID != shaderID)
            {
                m_currentShaderID = shaderID;
                m_currentTextureID = textureID;

                sprite->GetMaterial().DetachTexture();
                sprite->GetMaterial().DetachShader();

                sprite->GetMaterial().AttachShader();
                sprite->GetMaterial().AttachTexture();

                ProcessLights(sprite->GetMaterial().GetShader());
            }
            else if (m_currentTextureID != textureID)
            {
                sprite->GetMaterial().DetachTexture();
                sprite->GetMaterial().AttachTexture();

                m_currentTextureID = textureID;
            }

            UpdateVertices(dest);
            UpdateUVs(src, sprite->GetWidth(), sprite->GetHeight());
        }
    }

    void Renderer::DetachMesh(const Sprite* sprite) const
    {
        if (m_pSpriteMesh != nullptr && sprite != nullptr)
        {
            sprite->GetMaterial().DetachTexture();
        }
    }

    glm::mat4 Renderer::CalculateTransformMatrix(const RectF& dest, const float rotation) const
    {
        auto transform = glm::mat4(1.0f);
        transform = translate(transform, glm::vec3(dest.X, dest.Y, 0.0f));
        transform = rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = scale(transform, glm::vec3(1.0f, 1.0f, 0.0f));

        return transform;
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

    void Renderer::ProcessLights(const Shader& shader) const
    {
        if (m_pLightManager == nullptr)
            return;

        const Array<UniquePtr<Light>>& lights = m_pLightManager->GetLights();
        shader.SetUniformInt("LightCount", lights.size());

        for (UInt i = 0; i < lights.size(); i++)
        {
            const Light& light = *lights[i];

            shader.SetUniformVector2("Lights[" + std::to_string(i) + "].Pos", light.Position);
            shader.SetUniformColor("Lights[" + std::to_string(i) + "].Color", light.LightColor.Normalise());
            shader.SetUniformFloat("Lights[" + std::to_string(i) + "].Intensity", light.Intensity);
            shader.SetUniformFloat("Lights[" + std::to_string(i) + "].Radius", light.Radius);
        }
    }
}
