#ifndef PHYSICS_H
#define PHYSICS_H
#include <box2d/box2d.h>
#include "Core/TypeDefs.h"
#include "Core/Maths/Vector2.h"

namespace Core
{
    class DebugDraw;
    class Renderer;

    class Physics
    {
    private:
        static UniquePtr<b2World> m_pWorld;
        static UniquePtr<DebugDraw> m_pDebugDraw;

    public:
        Physics(Renderer& renderer);
        ~Physics();

        void Update() const;
        void Render(Renderer& renderer);

        static b2Body* CreateDynamicBody(Vector2F position, UInt width, UInt height);
        static b2Body* CreateStaticBody(Vector2F position, UInt width, UInt height);
        static void DestroyBody(b2Body* body);

        static DebugDraw& GetDebugDraw() { return *m_pDebugDraw; }
    };
}

#endif //PHYSICS_H
