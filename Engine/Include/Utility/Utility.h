#ifndef UTILITY_H
#define UTILITY_H
#include <chrono>
#include <random>
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

    class Random
    {
    private:
        std::mt19937 m_gen;
        std::random_device m_rd;

    public:
        Random() : m_gen(std::chrono::system_clock::now().time_since_epoch().count()) {}

        int GetInt(int min, int max)
        {
            std::uniform_int_distribution<int> dist(min, max);
            return dist(m_gen);
        }

        float GetFloat(float min, float max)
        {
            std::uniform_real_distribution<float> dist(min, max);
            return dist(m_gen);
        }

        int Choose(int num1, int num2)
        {
            std::uniform_int_distribution<int> dist(0, 1);
            return dist(m_gen) == 0 ? num1 : num2;
        }

        float GetFloat01() { return GetFloat(0.0f, 1.0f); }
    };
}

#endif //UTILITY_H
