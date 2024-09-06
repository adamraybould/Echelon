#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H
#include <box2d/b2_draw.h>

class b2World;

namespace Core
{
    class Renderer;

    class DebugDraw final : public b2Draw
    {
    private:
        Renderer& m_renderer;

    public:
        DebugDraw(Renderer& renderer);
        ~DebugDraw() override;

        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
        void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
        void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;
        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
        void DrawTransform(const b2Transform& xf) override;
        void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;

        void DrawBox2DCollision(b2World* world);
    };
}

#endif //DEBUGDRAW_H
