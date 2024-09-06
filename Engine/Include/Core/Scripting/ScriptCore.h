#ifndef SCRIPTCORE_H
#define SCRIPTCORE_H
#include "Core/TypeDefs.h"

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

namespace luabridge { class LuaRef; }

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
        bool m_isInitialised = false;

    public:
        ScriptCore();
        ~ScriptCore();

        void Update(float delta) const;
        void Render(Renderer& renderer);

        void RegisterBinder(IBinder* binder);
        void InitialiseBinders();

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
