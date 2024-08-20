#include "Main/IProgram.h"
#include "Main/Application.h"

namespace Engine
{
    IProgram* CreateProgram()
    {
        return new Application;
    }
}
