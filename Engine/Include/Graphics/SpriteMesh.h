#ifndef SPRITEMESH_H
#define SPRITEMESH_H
#include "Core/TypeDefs.h"
#include "Core/Maths/Vector2.h"

namespace Graphics
{
    struct Vertex
    {
        Vector2F Position;
        Vector2F UV;

        Vertex(const Vector2F position, const Vector2F uv) : Position(position), UV(uv) {}
    };

    struct Vector2F4X
    {
    private:
        Vector2F m_vectors[4];

    public:
        Vector2F4X(const Vector2F vec1, const Vector2F vec2, const Vector2F vec3, const Vector2F vec4)
        {
            m_vectors[0] = vec1;
            m_vectors[1] = vec2;
            m_vectors[2] = vec3;
            m_vectors[3] = vec4;
        }

        const Vector2F* GetArray() const { return m_vectors; }
    };

    class SpriteMesh
    {
    private:
        UInt VAO;
        UInt VBO;
        UInt TBO;
        UInt IBO;

    public:
        SpriteMesh();
        ~SpriteMesh();

        void AttachMesh() const;
        void DetachMesh() const;

        void UpdateVertexBuffer(Vector2F vertices[4]) const;
        void UpdateUVBuffer(Vector2F uvs[4]) const;

        UInt GetVAO() const { return VAO; }
        UInt GetVBO() const { return VBO; }
        UInt GetTBO() const { return TBO; }

    private:
        void Create();
        UInt CreateBuffer(UInt target, const void* data, UInt dataSize, UInt index, UInt size, UInt usage) const;
    };
}

#endif //SPRITEMESH_H
