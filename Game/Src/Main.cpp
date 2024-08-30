#include <iostream>

#include <SDL2/SDL.h>
#include "Echelon/Levels/MainLevel.h"
#include <Engine/Core/Interfaces/IProgram.h>
#include "Engine/Core/Application.h"
#include "Engine/Core/Systems/LevelManager.h"
#include "Engine/States/GameState.h"

int main(int argc, char *argv[])
{
    IProgram* program = CreateProgram();
    Application* application = static_cast<Application*>(program);

    GameState& gameState = static_cast<GameState&>(application->GetStateSystem().GetCurrentState());
    LevelManager& levelManager = gameState.GetLevelManager();

    levelManager.AddLevel<Echelon::Levels::MainLevel>();
    levelManager.LoadLevel(0);

    program->Run();

    delete program;
    std::cout << "Ending Program" << std::endl;

    return 0;
}
