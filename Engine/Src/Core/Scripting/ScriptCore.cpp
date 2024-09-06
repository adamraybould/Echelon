#include "Core/Scripting/ScriptCore.h"
#include "Core/Scripting/IBinder.h"
#include "Core/Maths/Rectangle.h"
#include "Core/Maths/Vector2.h"

#include "config.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

using namespace luabridge;
namespace Core
{
    ScriptCore* ScriptCore::m_pInstance;

    ScriptCore::ScriptCore() : L(nullptr)
    {
        m_pInstance = this;
        m_isInitialised = false;

        L = luaL_newstate();
        luaL_openlibs(L);

        SetupScriptPath();
    }

    ScriptCore::~ScriptCore()
    {
        if (L)
        {
            lua_close(L);
        }
    }

    void ScriptCore::Update(float delta) const
    {
        LRef update = getGlobal(L, "Update");
        if (!update.isNil() && update.isFunction())
        {
            update(delta);
        }
    }

    void ScriptCore::Render(Renderer& renderer)
    {
    }

    void ScriptCore::RegisterBinder(IBinder* binder)
    {
        m_binders.push_back(binder);
    }

    void ScriptCore::InitialiseBinders()
    {
        IBinder::InitialiseBinders();

        SetupEmbedding();
        GeneratePrefabsList();

        LoadScript("main.lua");
        LoadScript("update.lua");
    }

    bool ScriptCore::LoadScript(const char* fileName) const
    {
        // Loads and runs the .lua file
        std::string filePath = SCRIPTS_PATH + std::string(fileName);
        if (luaL_dofile(L, filePath.c_str()) != LUA_OK)
        {
            ReportError(lua_gettop(L));
            return false;
        }

        return true;
    }

    void ScriptCore::SetupScriptPath() const
    {
        lua_getglobal(L, "package");
        lua_getfield(L, -1, "path");
        std::string luaPath = lua_tostring(L, -1);
        lua_pop(L, 1);

        std::string path = ";" + std::string(SCRIPTS_PATH) + "?.lua";
        luaPath += path;

        lua_pushstring(L, luaPath.c_str());
        lua_setfield(L, -2, "path");
        lua_pop(L, 1);
    }

    void ScriptCore::SetupEmbedding()
    {
        // -- Vector2i
        getGlobalNamespace(L)
        .beginClass<Vector2F>("Vector2")
        .addConstructor<void(*)(float, float)>()
        .addProperty("x", &Vector2F::X)
        .addProperty("y", &Vector2F::Y)
        .addFunction("__tostring", &Vector2F::ToString)
        .endClass();

        // -- Rectangle
        getGlobalNamespace(L)
        .beginClass<RectF>("Rectangle")
        .addConstructor<void(*)(float, float, float, float)>()
        .addProperty("x", &RectF::X)
        .addProperty("y", &RectF::Y)
        .addProperty("w", &RectF::Width)
        .addProperty("h", &RectF::Height)
        //.addFunction("ContainsPoint", &RectF::ContainsPoint)
        .endClass();
    }

    void ScriptCore::GeneratePrefabsList()
    {
        Array<std::string> files = GetLuaFiles("Prefabs");

        const char* filename = "prefablist.lua";
        std::string path = SCRIPTS_PATH + std::string(filename);
        std::ofstream luaFile(path);
        if (!luaFile.is_open())
        {
            std::cerr << "Failed to open " << filename << " for writing." << std::endl;
            return;
        }

        luaFile << "PREFABFILES = {\n";
        for (const auto& file : files)
        {
            luaFile << "\"" << file << "\",\n";
        }

        luaFile << "}\n";
        luaFile.close();
    }

    Array<std::string> ScriptCore::GetLuaFiles(const std::string directory)
    {
        std::string path = SCRIPTS_PATH + directory;

        std::vector<std::string> files;
        try
        {
            for (const auto& entry : fs::directory_iterator(path))
            {
                if (entry.is_regular_file() && entry.path().extension() == ".lua")
                {
                    const std::string prefix = path + "/";

                    // Convert path to a standardized format (forward slashes)
                    std::string normalizedPath = entry.path().generic_string();
                    if (normalizedPath.find(prefix) == 0)
                        normalizedPath.erase(0, prefix.length());

                    normalizedPath.erase(normalizedPath.length() - 4, 4);
                    files.push_back(normalizedPath);
                }
            }
        }
        catch (const fs::filesystem_error& e)
        {
            std::cerr << "Error accessing directory: " << e.what() << std::endl;
        }

        return files;
    }


    void ScriptCore::ReportError(int status) const
    {
        if (status != LUA_OK)
        {
            std::cerr << "-- " << lua_tostring(L, status) << std::endl;
            lua_pop(L, 1);
        }
    }

    void ScriptCore::PrintGlobalTabel() const
    {
        lua_pushglobaltable(L);
        lua_pushnil(L);

        while (lua_next(L, -2) != 0)
        {
            if (lua_isstring(L, -2))
            {
                std::string key = lua_tostring(L, -2);
                std::cout << "Global name: " << key << std::endl;
            }

            lua_pop(L, 1);
        }

        lua_pop(L, 1);
    }
}
