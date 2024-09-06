#include "Core/System.h"

#include <iostream>
#include <ostream>
#include <SDL_error.h>
#include <windows.h>
#include <string>

namespace Core
{
    void System::PrintErrorMessage(const std::string& message)
    {
        std::cerr << message << std::endl;
    }

    void System::OutputError(const std::string& error, const std::string& errorTile, const bool shouldExit, const bool displaySDLError)
    {
        std::string errorMessage = std::string(error) + (displaySDLError ? SDL_GetError() : "");
        MessageBoxA(NULL, errorMessage.c_str(), errorTile.c_str(), MB_ICONERROR | MB_OK);

        if (shouldExit)
            exit(-1);
    }
}
