#ifndef COMMONS_H
#define COMMONS_H

#include "Engine/Core/Maths/Vector2.h"
#include "Engine/Core/Maths/Rectangle.h"

#include <cstdint>
#include <memory>
#include <vector>
#include <map>
#include <SDL2/SDL_stdinc.h>
#include <string>
#include <unordered_map>

using namespace Core::Maths;

using UInt = unsigned int;
using UInt32 = Uint32;
using UInt64 = int64_t;

using GUID = std::string;

template <typename T> using Array = std::vector<T>;
template <typename Key, typename Value> using Map = std::map<Key, Value>;
template <typename Key, typename Value> using UnorderedMap = std::unordered_map<Key, Value>;

template <typename T> using UniquePtr = std::unique_ptr<T>;
template <typename T> using SharedPtr = std::shared_ptr<T>;
template <typename T> using WeakPtr = std::weak_ptr<T>;

struct MinMaxRange
{
    float Min;
    float Max;

    MinMaxRange()
    {
        Min = 0.0f;
        Max = 0.0f;
    }

    MinMaxRange(float min, float max)
    {
        Min = min;
        Max = max;
    }
};

#endif //COMMONS_H
