#include <iostream>

#include "Echelon/Levels/MainLevel.h"
#include <Engine/Core/IProgram.h>
#include "Engine/Systems/LevelManager.h"

int main(int argc, char *argv[])
{
    IProgram* program = CreateProgram();

    Systems::LevelManager::GetInstance()->AddLevel<Echelon::Levels::MainLevel>();
    Systems::LevelManager::GetInstance()->LoadLevel(0);

    program->Run();

    delete program;
    std::cout << "Ending Program" << std::endl;

    return 0;
}
