#include <iostream>

#include "Levels/MainLevel.h"
#include "Main/IProgram.h"
#include "Systems/LevelManager.h"

int main(int argc, char *argv[])
{
    Engine::IProgram* program = Engine::CreateProgram();

    Engine::Systems::LevelManager::GetInstance()->AddLevel<Echelon::Levels::MainLevel>();
    Engine::Systems::LevelManager::GetInstance()->LoadLevel(0);

    program->Run();

    delete program;
    std::cout << "Ending Program" << std::endl;

    return 0;
}
