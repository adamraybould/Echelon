#ifndef SHADER_H
#define SHADER_H
#include <glm/glm.hpp>
#include "Core/TypeDefs.h"

namespace Rendering
{
    class Shader
    {
    private:
        UInt m_program;

    public:
        Shader(const String& path);
        ~Shader();

        void Use() const;
        void Detach() const;

        UInt GetUniformLocation(const String& name) const;
        void SetUniformMat4(const String& name, const glm::mat4& matrix) const;
        void SetUniformTexture2D(const String& name, UInt slot, const UInt& texture) const;

        UInt GetProgram() const { return m_program; }

    private:
        void Create(const String& path);
        UInt LoadShader(const UInt& program, UInt type, const String& source) const;

        void ReadShaderFile(const String& path, String& vertexShader, String& fragmentShader) const;
        void CheckForErrors(const UInt& shader, const UInt param) const;
    };
}

#endif //SHADER_H
