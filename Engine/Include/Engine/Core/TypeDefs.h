#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

namespace Core
{
    using UInt = unsigned int;
    using String = std::string;

    template <typename T> using Array = std::vector<T>;
    template <typename Key, typename Value> using Map = std::map<Key, Value>;
    template <typename Key, typename Value> using UnorderedMap = std::unordered_map<Key, Value>;

    template <typename T> using UniquePtr = std::unique_ptr<T>;
    template <typename T> using SharedPtr = std::shared_ptr<T>;
    template <typename T> using WeakPtr = std::weak_ptr<T>;
}

#endif //TYPEDEFS_H
