#include "Graphics/Sprite.h"

#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

#include "Core/Camera.h"
#include "Core/IO/Renderer.h"
#include "Graphics/Material.h"
#include "Graphics/Texture2D.h"
#include "Rendering/Shader.h"

using namespace Rendering;
namespace Graphics
{
    Sprite::Sprite(Texture2D& texture)
    {
        m_pMaterial = std::make_unique<Material>(texture, "Base.glsl");
    }

    Sprite::~Sprite()
    {
        if (m_pMaterial != nullptr)
        {
            m_pMaterial.reset();
        }
    }
}
