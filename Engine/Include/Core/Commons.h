#ifndef COMMONS_H
#define COMMONS_H

namespace Core
{
    struct MinMaxRange
    {
        float Min;
        float Max;

        MinMaxRange()
        {
            Min = 0.0f;
            Max = 0.0f;
        }

        MinMaxRange(const float min, const float max)
        {
            Min = min;
            Max = max;
        }
    };
}

#endif //COMMONS_H
