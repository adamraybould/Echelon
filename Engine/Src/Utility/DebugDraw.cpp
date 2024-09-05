#include "Engine/Utility/DebugDraw.h"

#include <box2d/box2d.h>
#include "Engine/Core/Renderer.h"
#include "Engine/Utility/Constants.h"

namespace Core
{
    DebugDraw::DebugDraw(Renderer& renderer) : m_renderer(renderer)
    {
    }

    DebugDraw::~DebugDraw()
    {
    }

    void DebugDraw::DrawPolygon(const b2Vec2* vertices, const int32 vertexCount, const b2Color& color)
    {
        SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255), static_cast<Uint8>(color.g * 255),
                               static_cast<Uint8>(color.b * 255), 255);

        for (int32 i = 0; i < vertexCount; ++i)
        {
            b2Vec2 p1 = vertices[i];
            b2Vec2 p2 = vertices[(i + 1) % vertexCount];

            SDL_RenderDrawLine(m_renderer, static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p2.x),
                               static_cast<int>(p2.y));
        }
    }

    void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
    }

    void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
    {
    }

    void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
    {
    }

    void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
    {
    }

    void DebugDraw::DrawTransform(const b2Transform& xf)
    {
    }

    void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
    {
    }

    void DebugDraw::DrawBox2DCollision(b2World* world)
    {
        for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
        {
            for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
            {
                const b2Shape* shape = fixture->GetShape();
                if (shape->GetType() == b2Shape::e_polygon)
                {
                    const b2PolygonShape* poly = static_cast<const b2PolygonShape*>(shape);

                    if (poly->m_count == 4)
                    {
                        // Ensure it's a rectangle
                        SDL_Point sdlPoints[4];

                        for (int i = 0; i < 4; ++i)
                        {
                            // Transform local vertex to world space
                            b2Vec2 worldVertex = body->GetWorldPoint(poly->m_vertices[i]);

                            // Convert world space to screen space
                            Vector2F screenPoint = Camera::Main->CalculateScreenPosition(Vector2F(worldVertex.x * PPM, worldVertex.y * PPM));

                            // Store the converted screen coordinates
                            sdlPoints[i].x = static_cast<int>(screenPoint.X);
                            sdlPoints[i].y = static_cast<int>(screenPoint.Y);
                        }

                        // Set draw color
                        SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255); // Green color for rectangles

                        // Draw the rectangle (polygon with 4 vertices)
                        SDL_RenderDrawLines(m_renderer, sdlPoints, 4);

                        // Optionally, close the rectangle loop
                        SDL_RenderDrawLine(m_renderer, sdlPoints[3].x, sdlPoints[3].y, sdlPoints[0].x, sdlPoints[0].y);
                    }
                }
            }
        }
    }
}
