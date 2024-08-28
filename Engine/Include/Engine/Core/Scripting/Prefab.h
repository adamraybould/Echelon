#ifndef PREFAB_H
#define PREFAB_H
#include "IBinder.h"

namespace Core
{
    namespace Scripting
    {
        enum AssetType
        {
            NIL,
            SPRITE,
            SOUND
        };

        struct PrefabAsset
        {
        private:
            AssetType m_type;
            String m_path;
            int m_param;

        public:
            PrefabAsset(const AssetType type, const String& path, const int param)
            {
                m_type = type;
                m_path = path;
                m_param = param;
            }

            AssetType GetType() const { return m_type; }
            String GetPath() { return m_path; }

            bool HasParams() const { return m_param != -1; }
            int GetParam() const { return m_param; }
        };

        using namespace luabridge;
        class Prefab : public IBinder
        {
        private:
            LState* m_pSelf;

            String m_name;
            UniquePtr<LRef> m_pPrefab = nullptr;
            Array<UniquePtr<PrefabAsset>> m_assets;

        public:
            Prefab(LState* self, const String& name, const LRef& prefab);
            ~Prefab() override;

            void SetupEmbedding(LState* L) override;
            GUID CallFn();

            PrefabAsset* GetAsset(AssetType type) const;

            LRef& GetPrefab() const { return *m_pPrefab;}
            bool IsValid() const;

        private:
            void ProcessAssets(LState* L, const LRef& assets);
            void RegisterAsset(LState* L, const LRef& asset);
        };
    }
}

#endif //PREFAB_H
