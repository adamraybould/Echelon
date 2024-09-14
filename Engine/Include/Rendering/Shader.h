#ifndef SHADER_H
#define SHADER_H
#include <glm/glm.hpp>

#include "Core/TypeDefs.h"
#include "Core/Commons.h"
#include "Core/Maths/Vector2.h"

namespace Rendering
{
    class Shader
    {
    private:
        UInt m_program = 0;
        UInt m_id = 0;

    public:
        Shader(const String& path);
        ~Shader();

        void Use() const;
        void Detach() const;

        UInt GetUniformLocation(const String& name) const;
        void SetUniformMat4(const String& name, const glm::mat4& matrix) const;
        void SetUniformTexture2D(const String& name, UInt slot, const UInt& texture) const;
        void SetUniformVector2(const String& name, const Vector2F& vector) const;
        void SetUniformColor(const String& name, const Color& color) const;

        void SetUniformInt(const String& name, int value) const;
        void SetUniformFloat(const String& name, float value) const;

        UInt GetProgram() const { return m_program; }
        UInt GetID() const { return m_id; }

    private:
        void Create(const String& path);
        UInt LoadShader(const UInt& program, UInt type, const String& source);

        void ReadShaderFile(const String& path, String& vertexShader, String& fragmentShader) const;
        void CheckForErrors(const UInt& shader, const UInt param) const;
    };
}

#endif //SHADER_H
