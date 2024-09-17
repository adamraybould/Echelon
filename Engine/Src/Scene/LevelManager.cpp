#include "Scene/LevelManager.h"

#include "Scene/Level.h"

namespace Scene
{
    UnorderedMap<String, UniquePtr<Level>> LevelManager::m_pLevels;

    LevelManager::LevelManager()
    {
    }

    LevelManager::~LevelManager()
    {
    }

    void LevelManager::SetupEmbedding(lua_State* L)
    {
        BindStaticFunction(L, "LevelManager", "RegisterLevel", &LevelManager::RegisterLevel);
        BindStaticFunction(L, "LevelManager", "LoadLevel", &LevelManager::LoadLevel);
        BindStaticFunction(L, "LevelManager", "GetLevel", &LevelManager::GetLevel);
    }

    void LevelManager::RegisterLevel(LState* L, const String& name, const LRef& levelTemplate)
    {
        UniquePtr<Level> level = std::make_unique<Level>(name, levelTemplate);
        m_pLevels.emplace(name, std::move(level));
    }

    void LevelManager::LoadLevel(LState* L, const String& name)
    {
        Level& level = *m_pLevels[name];
        if (level.IsValid())
        {
            level.Initialise();
        }
    }

    Level& LevelManager::GetLevel(const String& name)
    {
        if (m_pLevels.contains(name))
            return *m_pLevels[name].get();

        throw std::runtime_error("LevelManager::GetLevel: Level does not exist");
    }
}
