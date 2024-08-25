#ifndef IBINDER_H
#define IBINDER_H

#include <cstdint>
#include "ScriptCore.h"
#include <luabridge3/LuaBridge/LuaBridge.h>

namespace Core
{
    class IBinder
    {
    public:
        IBinder();
        virtual ~IBinder() = default;

        virtual void SetupEmbedding(lua_State* L) = 0;

    protected:
        template <typename T>
        void BindClass(lua_State* L)
        {
            using namespace luabridge;
            getGlobalNamespace(L).beginClass<T>(typeid(T).name()).endClass();
        }

        template <typename T>
        void BindClass(lua_State* L, const char* nsName)
        {
            using namespace luabridge;
            getGlobalNamespace(L).beginNamespace(nsName).beginClass<T>(typeid(T).name()).endClass().endNamespace();
        }

        template <typename T,  typename Getter>
        void BindProperty(lua_State* L, const char* propertyName, Getter get)
        {
            using namespace luabridge;
            getGlobalNamespace(L).beginClass<T>(typeid(T).name()).addProperty(propertyName, get).endClass();
        }

        template <typename T,  typename Getter, typename Setter>
        void BindProperty(lua_State* L, const char* propertyName, Getter get, Setter set)
        {
            using namespace luabridge;
            getGlobalNamespace(L).beginClass<T>(typeid(T).name()).addProperty(propertyName, get, set).endClass();
        }

        template <typename T,  typename Getter, typename Setter>
        void BindProperty(lua_State* L, const char* nsName, const char* propertyName, Getter get, Setter set)
        {
            using namespace luabridge;
            getGlobalNamespace(L).beginNamespace(nsName).beginClass<T>(typeid(T).name()).addProperty(propertyName, get, set).endClass().endNamespace();
        }

        template <typename Func>
        void BindFunction(lua_State* L, const char* nsName, const char* funcName, Func function)
        {
            using namespace luabridge;
            getGlobalNamespace(L).beginNamespace(nsName).addFunction(funcName, function).endNamespace();
        }

        template <typename T, typename Func>
        void BindFunction(lua_State* L, const char* nsName, const char* funcName, Func function)
        {
            using namespace luabridge;
            getGlobalNamespace(L).beginNamespace(nsName).beginClass<T>(typeid(T).name()).addFunction(funcName, function).endClass().endNamespace();
        }

        template <typename T, typename Func>
        void BindFunction(lua_State* L, const char* funcName, Func function)
        {
            using namespace luabridge;
            getGlobalNamespace(L).beginClass<T>(typeid(T).name()).addFunction(funcName, function).endClass();
        }

        template <typename Func>
        void BindStaticFunction(lua_State* L, const char* nsName, const char* funcName, Func function)
        {
            using namespace luabridge;
            getGlobalNamespace(L).beginNamespace(nsName).addFunction(funcName, function).endNamespace();
        }

        template <typename T, typename Func>
        void BindStaticFunction(lua_State* L, const char* funcName, Func function)
        {
            using namespace luabridge;
            getGlobalNamespace(L).beginClass<T>(typeid(T).name()).addStaticFunction(funcName, function).endClass();
        }

        template <typename T, typename Func>
        void BindStaticFunction(lua_State* L, const char* nsName, const char* funcName, Func function)
        {
            using namespace luabridge;
            getGlobalNamespace(L)
            .beginNamespace(nsName)
            .beginClass<T>(typeid(T).name())
            .addStaticFunction(funcName, function)
            .endClass()
            .endNamespace();
        }
    };
}

#endif //IBINDER_H
