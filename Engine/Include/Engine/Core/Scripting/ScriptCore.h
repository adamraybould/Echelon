#ifndef SCRIPTCORE_H
#define SCRIPTCORE_H
#include <string>
#include <unordered_map>
#include <vector>
#include "Engine/Utility/Commons.h"

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

template <typename T> using Array = std::vector<T>;
template <typename Key, typename Value> using UnorderedMap = std::unordered_map<Key, Value>;

namespace luabridge
{
    class LuaRef;
}

namespace Core
{
    class IBinder;
    class Renderer;

    class ScriptCore
    {
    private:
        static ScriptCore* m_pInstance;
        lua_State* L;

        Array<IBinder*> m_binders;
        //UnorderedMap<std::string, luabridge::LuaRef> m_componentBinders;

    public:
        ScriptCore();
        ~ScriptCore();

        void Update(float delta);
        void Render(Renderer& renderer);

        void AddBinder(IBinder* binder);
        void SetupBindings();

        bool LoadScript(const char* fileName) const;

        lua_State* GetLuaState() const { return L; }

        static ScriptCore* Instance() { return m_pInstance; }

    private:
        void SetupScriptPath() const;

        void SetupEmbedding();

        static void GeneratePrefabsList();
        static Array<std::string> GetLuaFiles(const std::string directory);

        void PrintGlobalTabel() const;
        void ReportError(int status) const;
    };
}

#endif //SCRIPTCORE_H
