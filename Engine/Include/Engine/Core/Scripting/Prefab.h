#ifndef PREFAB_H
#define PREFAB_H
#include "IBinder.h"

namespace Core
{
    namespace Scripting
    {
        using namespace luabridge;
        class Prefab : public IBinder
        {
        private:
            lua_State* m_self;
            const char* m_name = "";
            UniquePtr<LuaRef> m_fn;

        public:
            Prefab(lua_State* self, const char* name, LuaRef fn);
            ~Prefab();
            void SetupEmbedding(lua_State* L) override;

            GUID CallFn();

            void SetName(const char* name) { m_name = name; }
            const char* GetName() const { return m_name; }
        };
    }
}

#endif //PREFAB_H
