#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include "Core/Scripting/IBinder.h"


namespace Scene
{
    class Level;

    class LevelManager final : IBinder
    {
    private:
        static UnorderedMap<String, UniquePtr<Level>> m_pLevels;

    public:
        LevelManager();
        ~LevelManager() override;

        void SetupEmbedding(lua_State* L) override;

        static void RegisterLevel(LState* L, const String& name, const LRef& levelTemplate);
        static void LoadLevel(LState* L, const String& name);
        static Level& GetLevel(const String& name);
    };
}

#endif //LEVELMANAGER_H
