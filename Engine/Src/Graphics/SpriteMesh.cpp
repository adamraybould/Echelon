#include "Graphics/SpriteMesh.h"
#include <GL/glew.h>

namespace Graphics
{
    Vector2F vertices[] =
    {
        Vector2F(1.0f, 1.0f),
        Vector2F(1.0f, -1.0f),
        Vector2F(-1.0f, -1.0f),
        Vector2F(-1.0f, 1.0f)
    };

    Vector2F UVs[] =
    {
        Vector2F(1.0f, 1.0f),
        Vector2F(1.0f, 0.0f),
        Vector2F(0.0f, 0.0f),
        Vector2F(0.0f, 1.0f)
    };

    const UInt indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    SpriteMesh::SpriteMesh()
    {
        VAO = 0;
        VBO = 0;
        TBO = 0;
        IBO = 0;

        Create();
    }

    SpriteMesh::~SpriteMesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &TBO);
        glDeleteBuffers(1, &IBO);
    }

    void SpriteMesh::AttachMesh() const
    {
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    }

    void SpriteMesh::DetachMesh() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
    }

    void SpriteMesh::UpdateVertexBuffer(Vector2F vertices[4]) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vector2F) * 4, vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void SpriteMesh::UpdateUVBuffer(Vector2F uvs[4]) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, TBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vector2F) * 4, uvs);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void SpriteMesh::Create()
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        VBO = CreateBuffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices), 0, 2, GL_DYNAMIC_DRAW);
        TBO = CreateBuffer(GL_ARRAY_BUFFER, UVs, sizeof(UVs), 1, 2, GL_DYNAMIC_DRAW);
        IBO = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices), 0, 2, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    UInt SpriteMesh::CreateBuffer(const UInt target, const void* data, const UInt dataSize, const UInt index, const UInt size, const UInt usage) const
    {
        UInt buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(target, buffer);
        glBufferData(target, dataSize, data, usage);

        if (target == GL_ARRAY_BUFFER)
        {
            glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(index);
        }

        return buffer;
    }
}
