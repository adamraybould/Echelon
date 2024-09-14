#include "Rendering/Shader.h"

#include "config.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Rendering
{
    Shader::Shader(const String& path)
    {
        Create(path);
    }

    Shader::~Shader()
    {
        if (m_program)
        {
            glDeleteProgram(m_program);
        }
    }

    void Shader::Use() const
    {
        glUseProgram(m_program);
    }

    void Shader::Detach() const
    {
        glUseProgram(0);
    }

    UInt Shader::GetUniformLocation(const String& name) const
    {
        GLuint location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1)
            std::cerr << "Warning: Uniform Variable not found in Shader '" << name << "'" << std::endl;

        return location;
    }

    void Shader::Create(const String& path)
    {
        String vertexShader;
        String fragmentShader;
        ReadShaderFile(SHADERS_PATH + path, vertexShader, fragmentShader);

        m_program = glCreateProgram();
        const GLuint vertex = LoadShader(m_program, GL_VERTEX_SHADER, vertexShader);
        const GLuint fragment = LoadShader(m_program, GL_FRAGMENT_SHADER, fragmentShader);
        glLinkProgram(m_program);

        // Check for Linker Errors
        GLint status;
        glGetShaderiv(m_program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint logLength;
            glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> log(logLength);
            glGetProgramInfoLog(m_program, logLength, &logLength, log.data());
            std::cerr << "Program linking error: " << log.data() << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::SetUniformMat4(const String& name, const glm::mat4& matrix) const
    {
        const GLuint location = GetUniformLocation(name);
        if (location != -1)
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        }
    }

    void Shader::SetUniformTexture2D(const String& name, const UInt slot, const UInt& texture) const
    {
        const GLuint location = GetUniformLocation(name);
        if (location != -1)
        {
            glUniform1i(location, slot);
        }
    }

    void Shader::SetUniformVector2(const String& name, const Vector2F& vector) const
    {
        const GLuint location = GetUniformLocation(name);
        if (location != -1)
        {
            glUniform2f(location, vector.X, vector.Y);
        }
    }

    void Shader::SetUniformColor(const String& name, const Color& color) const
    {
        const GLuint location = GetUniformLocation(name);
        if (location != -1)
        {
            glUniform3f(location, color.R, color.G, color.B);
        }
    }

    void Shader::SetUniformInt(const String& name, const int value) const
    {
        const GLuint location = GetUniformLocation(name);
        if (location != -1)
        {
            glUniform1i(location, value);
        }
    }

    void Shader::SetUniformFloat(const String& name, const float value) const
    {
        const GLuint location = GetUniformLocation(name);
        if (location != -1)
        {
            glUniform1f(location, value);
        }
    }

    UInt Shader::LoadShader(const UInt& program, const UInt type, const String& source)
    {
        m_id += source.size();
        const char* data = source.c_str();

        const GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &data, nullptr);
        glCompileShader(shader);
        glAttachShader(program, shader);

        CheckForErrors(shader, GL_COMPILE_STATUS);
        return shader;
    }

    void Shader::ReadShaderFile(const String& path, String& vertexShader, String& fragmentShader) const
    {
        std::ifstream file(path);
        if (!file.is_open())
            throw std::runtime_error("Failed to open file: " + path);

        String line;
        std::stringstream vertexStream;
        std::stringstream fragmentStream;
        std::stringstream* currentStream = nullptr;

        while (std::getline(file, line))
        {
            if (line.find("#pragma Vertex") != std::string::npos)
                currentStream = &vertexStream;
            else if (line.find("#pragma Fragment") != std::string::npos)
                currentStream = &fragmentStream;
            else if (currentStream)
                *currentStream << line << '\n';
        }

        vertexShader = vertexStream.str();
        fragmentShader = fragmentStream.str();
    }

    void Shader::CheckForErrors(const UInt& shader, const UInt param) const
    {
        GLint status;
        glGetShaderiv(shader, param, &status);
        if (status == GL_FALSE)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "Shader Error: " << infoLog << std::endl;
        }
    }
}
