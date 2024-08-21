#ifndef MATHF_H
#define MATHF_H

namespace Core
{
    class MathF
    {
    public:
        static float Clamp(const float value, const float min, const float max)
        {
            return value < min ? min : value > max ? max : value;
        }

        static int Clamp(const int value, const int min, const int max)
        {
            return value < min ? min : value > max ? max : value;
        }

        static float Lerp(float start, float end, float factor)
        {
            return start + (end - start) * factor;
        }

        static Vector2 Lerp(const Vector2& start, const Vector2& end, const float factor)
        {
            float x = start.X + (end.X - start.X) * factor;
            float y = start.Y + (end.Y - start.Y) * factor;

            return Vector2(x, y);
        }
    };
}

#endif //MATHF_H
