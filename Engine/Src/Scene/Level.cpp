#include "Scene/Level.h"

#include "Core/Utility.h"
#include "Graphics/TileMap/TileMap.h"

using namespace Graphics;
namespace Scene
{
    Level::Level(const String& name, const LRef& levelTemplate)
    {
        m_name = name;
        m_pTemplate = std::make_unique<LRef>(levelTemplate);
        m_id = Utility::GenerateGUID();

        m_pMap = std::make_unique<TileMap>();
    }

    Level::~Level()
    {
        m_pMap.reset();
    }

    void Level::SetupEmbedding(lua_State* L)
    {
        BindFunction<Level>(L, "LoadMap", &Level::LoadMap);

        BindProperty<Level>(L, "Name", &Level::GetName);
        BindProperty<Level>(L, "ID", &Level::GetLevelID);
    }

    void Level::Initialise() const
    {
        LRef init = (*m_pTemplate)["init"];
        if (init)
        {
            if (init.isFunction())
            {
                try
                {
                    luabridge::LuaResult result = init();
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

    void Level::LoadMap(LState* L, const String& name)
    {
        if (m_pMap != nullptr)
        {
            m_pMap->LoadTileMap(name);
        }
    }

    bool Level::IsValid() const
    {
        return m_pTemplate != nullptr && (*m_pTemplate)["init"].isFunction();
    }
}
