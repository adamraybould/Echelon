#ifndef UTILITY_H
#define UTILITY_H
#include <chrono>

#include "Commons.h"

namespace Engine
{
    class Utility
    {
    private:
        static UInt64 IDCounter;

    public:
        static UInt64 GenerateUniqueID()
        {
            auto now = std::chrono::high_resolution_clock::now();
            auto timestamp = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();

            IDCounter++;
            Uint64 ID = (timestamp << 32) | IDCounter;
            return ID;
        }
    };
}

#endif //UTILITY_H
