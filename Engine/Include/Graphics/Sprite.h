#ifndef SPRITE_H
#define SPRITE_H
#include "Core/TypeDefs.h"

namespace Graphics
{
    class SpriteMesh;
    class Texture2D;
    class Material;

    class Sprite
    {
    private:
        UniquePtr<Material> m_pMaterial;

    public:
        explicit Sprite(Texture2D& texture);
        ~Sprite();

        Material& GetMaterial() const { return *m_pMaterial; }
        UInt GetWidth() const;
        UInt GetHeight() const;
    };
}

#endif //SPRITE_H
