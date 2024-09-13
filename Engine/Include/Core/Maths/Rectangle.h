#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vector2.h"
#include <SDL2/SDL_rect.h>

namespace Core
{
    template <typename T>
    struct Rectangle
    {
        T X;
        T Y;
        T Width;
        T Height;

        Rectangle() { X = 0; Y = 0; Width = 0; Height = 0; }
        Rectangle(T x, T y, T w, T h) { X = x; Y = y; Width = w; Height = h; }

        /* Returns if a Point is within the bounds of this Rectangle */
        bool ContainsPoint(const Vector2F& point) const
        {
            return point.X >= Left() && point.X <= Right() &&
                point.Y >= Top() && point.Y <= Bottom();
        }

        /* Returns if a Point is within the bounds of this Rectangle */
        bool ContainsPoint(const Vector2I& point) const
        {
            return point.X >= Left() && point.X <= Right() &&
                point.Y >= Top() && point.Y <= Bottom();
        }

        bool Intersects(const Rectangle& other) const
        {
            return Left() < other.Right() && Right() > other.Left() &&
                Top() < other.Bottom() && Bottom() > other.Top();
        }

        bool IsZero() const { return Width == 0 && Height == 0; }
        bool IsEqual(const Rectangle& other) { return X == other.X && Y == other.Y && Width == other.Width && Height == other.Height; }

        float Left() const { return X - Width * 0.5f; }
        float Right() const { return X + Width * 0.5f; }
        float Top() const { return Y - Height * 0.5f; }
        float Bottom() const { return Y + Height * 0.5f; }

        operator SDL_Rect() const
        {
            SDL_Rect rect;
            rect.x = X;
            rect.y = Y;
            rect.w = Width;
            rect.h = Height;
            return rect;
        }
    };

    using RectI = Rectangle<int>;
    using RectU = Rectangle<unsigned>;
    using RectF = Rectangle<float>;
}

#endif //RECTANGLE_H
