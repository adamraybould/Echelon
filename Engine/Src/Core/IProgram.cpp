#include "Engine/Core/IProgram.h"
#include "Engine/Core/Application.h"

namespace Core
{
    IProgram* CreateProgram()
    {
        return new Application;
    }
}
