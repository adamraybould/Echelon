#ifndef LEVEL_H
#define LEVEL_H
#include "Core/Scripting/IBinder.h"

namespace Graphics { class TileMap; }

namespace Scene
{
    class Level : IBinder
    {
    private:
        String m_name;
        UniquePtr<LRef> m_pTemplate = nullptr;
        GUID m_id; // Unique Level ID

        UniquePtr<Graphics::TileMap> m_pMap;

    public:
        Level(const String& name, const LRef& levelTemplate);
        ~Level() override;
        void SetupEmbedding(lua_State* L) override;

        void Initialise() const;

        void LoadMap(LState* L, const String& name);

        String GetName() const { return m_name; }
        GUID GetLevelID() const { return m_id; }

        bool IsValid() const;
    };
}

#endif //LEVEL_H
