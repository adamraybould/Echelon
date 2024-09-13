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

        void Attach() const;
        void Detach() const;

        Texture2D& GetTexture() const { return m_texture; }
        UInt GetTextureWidth() const;
        UInt GetTextureHeight() const;

        Rendering::Shader& GetShader() const { return *m_pShader; }
    };
}

#endif //MATERIAL_H
