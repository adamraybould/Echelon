#include "Engine/Main/EngineInterface.h"
#include "Engine/Main/Application.h"

MapleEngine::IApplication* MapleEngine::CreateApplication()
{
    return new Application;
}
