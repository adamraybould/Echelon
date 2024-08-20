#ifndef IPROGRAM_H
#define IPROGRAM_H

namespace Engine
{
    class IProgram
    {
    public:
        virtual ~IProgram() = default;
        virtual void Run() = 0;
    };

    extern "C" IProgram* CreateProgram();
}

#endif //IPROGRAM_H
