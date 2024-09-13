#ifndef SPRITE_H
#define SPRITE_H
#include <glm/fwd.hpp>

#include "Material.h"
#include "Texture2D.h"
#include "Core/TypeDefs.h"
#include "Core/Maths/Rectangle.h"

namespace Rendering { class Shader; }

namespace Graphics
{
    class SpriteMesh;
    class Material;

    class Sprite
    {
    private:
        UniquePtr<Material> m_pMaterial;

    public:
        explicit Sprite(Texture2D& texture);
        ~Sprite();

        Material& GetMaterial() const { return *m_pMaterial; }
        UInt GetWidth() const { return GetMaterial().GetTextureWidth(); }
        UInt GetHeight() const { return GetMaterial().GetTextureHeight(); }
    };
}

#endif //SPRITE_H
