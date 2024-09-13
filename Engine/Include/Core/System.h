#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>

namespace Core
{
    class System
    {
    public:
        System() = default;
        virtual ~System() = default;

    protected:
        static void PrintErrorMessage(const std::string& message);
        static void OutputError(const std::string& error, const std::string& errorTile, bool displaySDLError = false);
        static void Exit();
    };
}

#endif //SYSTEM_H
