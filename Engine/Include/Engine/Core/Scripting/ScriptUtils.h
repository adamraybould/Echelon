#ifndef SCRIPTUTILS_H
#define SCRIPTUTILS_H

#include "Engine/Core/ECS/Entity.h"

namespace Core
{
    inline void CreateEntity(lua_State* L)
    {
        using namespace luabridge;
        getGlobalNamespace(L).addFunction("CreateEntity", []() -> Entity* { return new Entity("Default"); });
    }
}

#endif //SCRIPTUTILS_H
