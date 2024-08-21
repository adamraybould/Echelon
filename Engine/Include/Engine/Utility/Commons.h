#ifndef COMMONS_H
#define COMMONS_H

#include "Engine/Core/Maths/Vector2.h"
#include "Engine/Core/Maths/Rectangle.h"

#include <cstdint>
#include <memory>
#include <SDL_stdinc.h>
#include <vector>
#include <map>

using namespace Core::Maths;

using UInt = unsigned int;
using UInt32 = Uint32;
using UInt64 = int64_t;

template <typename T> using Array = std::vector<T>;
template <typename Key, typename Value> using Map = std::map<Key, Value>;

template <typename T> using UniquePtr = std::unique_ptr<T>;
template <typename T> using SharedPtr = std::shared_ptr<T>;
template <typename T> using WeakPtr = std::weak_ptr<T>;

#endif //COMMONS_H
