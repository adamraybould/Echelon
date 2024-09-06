#include "Core/Scripting/Prefab.h"
#include "Core/Scripting/Engine.h"
#include <magic_enum.hpp>

namespace Core
{
    namespace Scripting
    {
        Prefab::Prefab(LState* self, const String& name, const LRef& prefab)
        {
            m_pSelf = self;
            m_name = name;
            m_pPrefab = std::make_unique<LRef>(prefab);

            if (!prefab["assets"].isNil())
            {
                ProcessAssets(self, prefab["assets"]);
            }
        }

        Prefab::~Prefab()
        {
            m_pSelf = nullptr;
            m_name = "";

            if (m_pPrefab)
                m_pPrefab.reset();
        }

        void Prefab::SetupEmbedding(LState* L)
        {
            using namespace luabridge;
            BindClass<Prefab>(L);
            getGlobalNamespace(L).beginClass<Prefab>("Prefab").addConstructor<void (*)(LState*, String, LRef)>().endClass();
        }

        GUID Prefab::CallFn()
        {
            LRef fn = (*m_pPrefab)["fn"];

            if (fn)
            {
                if (fn.isFunction())
                {
                    try
                    {
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

            return "";
        }

        PrefabAsset* Prefab::GetAsset(const AssetType type) const
        {
            for (UInt i = 0; i < m_assets.size(); i++)
            {
                if (m_assets[i]->GetType() == type)
                {
                    return m_assets[i].get();
                }
            }

            // Return Blank Asset
            return nullptr;
        }

        bool Prefab::IsValid() const
        {
            return m_pPrefab != nullptr && (*m_pPrefab)["fn"].isFunction();
        }

        void Prefab::ProcessAssets(LState* L, const LRef& assets)
        {
            if (assets.isTable())
            {
                for (Iterator it(assets); !it.isNil(); ++it)
                {
                    LRef asset = it.value();
                    RegisterAsset(L, asset);
                }
            }
            else
            {
                std::cerr << "Error: Failed to Process Assets for Prefab" << std::endl;
            }
        }

        void Prefab::RegisterAsset(LState* L, const LRef& asset)
        {
            if (asset.isTable())
            {
                String type = asset["type"].tostring();
                String path = asset["file"].tostring();

                int param = -1;
                if (!asset["param"].isNil() && asset["param"].isNumber())
                {
                    param = asset["param"];
                }

                std::optional<AssetType> typeOpt = magic_enum::enum_cast<AssetType>(type);
                if (typeOpt.has_value())
                {
                    m_assets.push_back(std::make_unique<PrefabAsset>(typeOpt.value(), path, param));
                }
                else
                {
                    std::cerr << "Error: Failed to convert 'Type' to a AssetType Enum" << std::endl;
                }
            }
            else
            {
                std::cerr << "Error: Failed to Register Asset" << std::endl;
            }
        }
    }
}
