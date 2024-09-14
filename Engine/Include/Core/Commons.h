#ifndef COMMONS_H
#define COMMONS_H

namespace Core
{
    struct Color
    {
        int R;
        int G;
        int B;

        Color() { R = 0; G = 0; B = 0; }
        Color(const int r, const int g, const int b) { R = r; G = g; B = b; }

        Color Normalise() const { return Color(R / 255, G / 255, B / 255); }
    };

    template <typename T>
    struct MinMaxRange
    {
        T Min;
        T Max;

        MinMaxRange()
        {
            Min = 0;
            Max = 0;
        }

        MinMaxRange(const T min, const T max)
        {
            Min = min;
            Max = max;
        }

    };

    using MinMaxRangeI = MinMaxRange<int>;
    using MinMaxRangeU = MinMaxRange<unsigned>;
    using MinMaxRangeF = MinMaxRange<float>;
}

#endif //COMMONS_H
