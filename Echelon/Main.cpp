#include <Engine/Main/EngineInterface.h>
#include <Engine/Utils/StateManager.h>
#include "Game/States/GameState.h"
#include <memory>
#include <iostream>

int main(int argc, char* argv[])
{
    MapleEngine::IApplication* application = MapleEngine::CreateApplication();
    MapleEngine::StateManager::GetInstance().LoadState<Echelon::GameState>();

    application->Run();

    delete application;
    std::cout << "Quitting Application" << std::endl;
}
