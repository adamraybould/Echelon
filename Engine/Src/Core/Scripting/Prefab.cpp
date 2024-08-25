#include "Engine/Core/Scripting/Prefab.h"

namespace Core
{
    namespace Scripting
    {
        Prefab::Prefab(lua_State* self, const char* name, LuaRef fn) : m_self(self), m_name(name)
        {
            m_name = name;
            m_fn = std::make_unique<LuaRef>(fn);
        }

        Prefab::~Prefab()
        {
            m_fn.reset();
        }

        void Prefab::SetupEmbedding(lua_State* L)
        {
            using namespace luabridge;
            BindClass<Prefab>(L);
            getGlobalNamespace(L).beginClass<Prefab>("Prefab").addConstructor<void (*)(lua_State*, const char*, LuaRef)>().endClass();
            BindProperty<Prefab>(L, "name", &Prefab::GetName, &Prefab::SetName);
            BindFunction<Prefab>(L, "fn", &Prefab::CallFn);
        }

        GUID Prefab::CallFn()
        {
            if (m_fn)
            {
                if (m_fn->isFunction())
                {
                    try
                    {
                        LuaRef fn = *m_fn;
                        LuaResult result = fn();
                        LuaRef entityRef = result[0];

                        return entityRef["GUID"];
                    }
                    catch (luabridge::LuaException const& e)
                    {
                        std::cerr << "Error in Lua Function: " << e.what() << std::endl;
                    }
                }
                else
                {
                    std::cerr << "No valid Lua Function Found" << std::endl;
                }
            }
        }
    }
}