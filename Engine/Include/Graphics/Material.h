#ifndef MATERIAL_H
#define MATERIAL_H
#include "Core/TypeDefs.h"

namespace Rendering { class Shader; }

namespace Graphics
{
    class Texture2D;

    class Material
    {
    private:
        Texture2D& m_texture;
        UniquePtr<Rendering::Shader> m_pShader;

    public:
        Material(Texture2D& texture, const String& shaderPath);
        ~Material();

        void AttachShader() const;
        void DetachShader() const;

        void AttachTexture() const;
        void DetachTexture() const;

        Texture2D& GetTexture() const { return m_texture; }
        UInt GetTextureWidth() const;
        UInt GetTextureHeight() const;

        Rendering::Shader& GetShader() const { return *m_pShader; }
    };
}

#endif //MATERIAL_H
