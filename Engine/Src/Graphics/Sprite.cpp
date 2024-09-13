#include "Graphics/Sprite.h"

#include "Core/Camera.h"
#include "Graphics/Material.h"

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

    UInt Sprite::GetWidth() const { return m_pMaterial->GetTextureWidth(); }
    UInt Sprite::GetHeight() const { return m_pMaterial->GetTextureHeight(); }
}
