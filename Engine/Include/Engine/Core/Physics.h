#ifndef PHYSICS_H
#define PHYSICS_H
#include <box2d/box2d.h>
#include "Engine/Utility/Commons.h"

namespace Core
{
    namespace Utility { class DebugDraw; }

    class Renderer;

    class Physics
    {
    private:
        static UniquePtr<b2World> m_pWorld;
        static UniquePtr<Utility::DebugDraw> m_pDebugDraw;

    public:
        Physics(Renderer& renderer);
        ~Physics();

        void Update() const;
        void Render(Renderer& renderer);

        static b2Body* CreateDynamicBody(Vector2 position, const UInt width, const UInt height);
        static b2Body* CreateStaticBody(Vector2 position, const UInt width, const UInt height);
        static void DestroyBody(b2Body* body);

        static Utility::DebugDraw& GetDebugDraw() { return *m_pDebugDraw; }
    };
}

#endif //PHYSICS_H
