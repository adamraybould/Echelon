#ifndef IPROGRAM_H
#define IPROGRAM_H

namespace Core
{
    class Application;

    class IProgram
    {
    public:
        virtual ~IProgram() = default;
        virtual void Run() = 0;
    };

    extern "C" IProgram* CreateProgram();
}

#endif //IPROGRAM_H
