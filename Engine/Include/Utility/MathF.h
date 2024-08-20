#ifndef MATHF_H
#define MATHF_H

namespace Engine
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
    };
}

#endif //MATHF_H
