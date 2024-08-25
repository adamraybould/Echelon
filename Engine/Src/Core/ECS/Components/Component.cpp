#include "Engine/Core/ECS/Components/Component.h"

#include "Engine/Core/ECS/Entity.h"
#include "Engine/Utility/Utility.h"

namespace Core::Components
{
    Component::Component(Entity& owner) : m_rOwner(owner), m_isActive(true)
    {
        m_guid = Utility::GenerateGUID();
    }

    void Component::SetupEmbedding(lua_State* L)
    {
        using namespace luabridge;
        getGlobalNamespace(L).beginClass<Component>("Component")
        .addConstructor<void (*)(Entity&)>()
        .addFunction("Update", &Component::Update)
        .addFunction("Render", &Component::Render)
        .endClass();
    }
}
