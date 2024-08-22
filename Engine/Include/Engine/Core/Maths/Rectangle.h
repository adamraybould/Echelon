#ifndef RECTANGLE_H
#define RECTANGLE_H

struct SDL_Rect;
namespace Core::Maths
{
    struct Rectangle
    {
        float X;
        float Y;
        float Width;
        float Height;

        Rectangle()
        {
            X = 0.0f;
            Y = 0.0f;
            Width = 0.0f;
            Height = 0.0f;
        }

        Rectangle(float x, float y, float w, float h)
        {
            X = x;
            Y = y;
            Width = w;
            Height = h;
        }

        /* Checks if a Point is contained within this Rect */
        bool ContainsPoint(const Vector2& point) const
        {
            return (point.X >= Left() && point.X <= Right() &&
                point.Y >= Top() && point.Y <= Bottom());
        }

        bool IsZero() const { return Width == 0.0f && Height == 0.0f; }

        float Left() const { return X - Width * 0.5f; }
        float Right() const { return X + Width * 0.5f; }
        float Top() const { return Y - Height * 0.5f; }
        float Bottom() const { return Y + Height * 0.5f; }

        explicit operator SDL_Rect* () const;
    };
}

#endif //RECTANGLE_H
