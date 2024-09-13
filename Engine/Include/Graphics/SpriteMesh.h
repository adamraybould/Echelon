#ifndef SPRITEMESH_H
#define SPRITEMESH_H

#include "Core/TypeDefs.h"
#include "Core/Maths/Vector2.h"

namespace Graphics
{
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
