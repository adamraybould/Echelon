#include "Graphics/Material.h"

#include "Graphics/Texture2D.h"
#include "Rendering/Shader.h"
#include <GL/glew.h>

using namespace Rendering;
namespace Graphics
{
    Material::Material(Texture2D& texture, const String& shaderPath) : m_texture(texture)
    {
        m_pShader = std::make_unique<Shader>(shaderPath);
    }

    Material::~Material()
    {
        m_pShader.reset();
    }

    void Material::AttachShader() const
    {
        if (m_pShader == nullptr)
            return;

        m_pShader->Use();
    }

    void Material::DetachShader() const
    {
        if (m_pShader == nullptr)
            return;

        m_pShader->Detach();
    }

    void Material::AttachTexture() const
    {
        if (m_pShader == nullptr)
            return;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        m_pShader->SetUniformTexture2D("TEX", 0, m_texture);
    }

    void Material::DetachTexture() const
    {
        if (m_pShader == nullptr)
            return;

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    UInt Material::GetTextureWidth() const { return m_texture.GetWidth(); }
    UInt Material::GetTextureHeight() const { return m_texture.GetHeight(); }
}
