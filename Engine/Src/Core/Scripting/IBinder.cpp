#include "Core/Scripting/IBinder.h"

namespace Core
{
    std::vector<std::function<void()>> IBinder::static_registry;

    IBinder::IBinder()
    {
        static_registry.push_back([this]() { SetupEmbedding(ScriptCore::Instance()->GetLuaState()); });
        //ScriptCore::Instance()->RegisterBinder(this);
    }

    void IBinder::InitialiseBinders()
    {
        for (const auto & binder : static_registry)
        {
            binder();
        }
    }
}
