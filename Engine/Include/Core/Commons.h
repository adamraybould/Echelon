#ifndef COMMONS_H
#define COMMONS_H

namespace Core
{
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
