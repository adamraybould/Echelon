#include "Engine/Core/Scripting/IBinder.h"
#include "Engine/Core/Scripting/ScriptCore.h"

namespace Core
{
    IBinder::IBinder()
    {
        ScriptCore* scriptCore = ScriptCore::Instance();
        scriptCore->AddBinder(this);
    }
}
