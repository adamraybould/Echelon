#include "Core/IProgram.h"
#include "Core/Application.h"

namespace Core
{
    IProgram* CreateProgram()
    {
        return new Application;
    }
}
