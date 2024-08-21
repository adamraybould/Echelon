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

        float Left() const { return X; }
        float Right() const { return X + Width; }
        float Top() const { return Y; }
        float Bottom() const { return Y + Height; }

        explicit operator SDL_Rect* () const;
    };
}

#endif //RECTANGLE_H
