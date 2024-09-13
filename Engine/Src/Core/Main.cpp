#include <iostream>

#include <SDL2/SDL.h>
#include <Core/IProgram.h>
#include "Core/Application.h"
#include "Systems/LevelManager.h"
#include "States/GameState.h"

int main(int argc, char *argv[])
{
    IProgram* program = CreateProgram();
    Application* application = static_cast<Application*>(program);

    const GameState& gameState = static_cast<GameState&>(application->GetStateSystem().GetCurrentState());
    LevelManager& levelManager = gameState.GetLevelManager();

    program->Run();

    delete program;
    std::cout << "Ending Program" << std::endl;

    return 0;
}
