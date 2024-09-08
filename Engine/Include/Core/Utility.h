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
            const xg::Guid guid = xg::newGuid();
            return guid.str();
        }

        /* Returns the String split between a specific symbol (Such as '#').
        You can choose to retrieve the String before or after the Symbol
        */
        static String SplitString(const String& str, const char symbol, const bool getBefore = true)
        {
            String splitStr = "";
            if (!str.empty())
            {
                UInt hashPos = str.find(symbol);
                if (hashPos != String::npos)
                {
                    if (getBefore)
                    {
                        splitStr = str.substr(0, hashPos);
                        splitStr.erase(splitStr.find_last_not_of(" \n\r\t") + 1);
                    }
                    else
                    {
                        splitStr = str.substr(hashPos + 1);
                        splitStr.erase(0, splitStr.find_first_not_of(" \n\r\t"));
                    }

                    return splitStr;
                }
            }

            // If failed, SplitStr will be empty.
            return splitStr;
        }

        static String Capitalize(const String& str)
        {
            String cStr = str;
            cStr[0] = std::toupper(cStr[0]);
            return cStr;
        }

        static String RemovePrefix(const String& string, const String& prefix)
        {
            size_t pos = string.find(prefix);
            if (pos != std::string::npos)
            {
                return string.substr(pos + prefix.length());
            }

            return string;
        }
    };

    class Random
    {
    private:
        std::random_device m_rd;
        std::mt19937 m_gen;

    public:
        Random() : m_gen(m_rd()) {}

        int GetInt(const int min, const int max)
        {
            std::uniform_int_distribution<int> dist(min, max);
            return dist(m_gen);
        }

        float GetFloat(const float min, const float max)
        {
            std::uniform_real_distribution<float> dist(min, max);
            return dist(m_gen);
        }

        int Choose(const int num1, const int num2)
        {
            std::uniform_int_distribution<int> dist(0, 1);
            return dist(m_gen) == 0 ? num1 : num2;
        }

        float GetFloat01() { return GetFloat(0.0f, 1.0f); }
    };
}

#endif //UTILITY_H
