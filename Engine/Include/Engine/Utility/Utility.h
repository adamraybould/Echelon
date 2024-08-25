#ifndef UTILITY_H
#define UTILITY_H
#include <chrono>
#include <random>
#include <crossguid/guid.hpp>

namespace Core
{
    class Utility
    {
    public:
        static GUID GenerateGUID()
        {
            xg::Guid guid = xg::newGuid();
            return guid.str();
        }
    };

    class Random
    {
    private:
        std::random_device m_rd;
        std::mt19937 m_gen;

    public:
        Random() : m_gen(m_rd()) {}

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
