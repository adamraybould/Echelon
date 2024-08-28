#include "Engine/Core/ECS/Entity.h"

#include "Engine/Core/God.h"
#include "Engine/Core/ECS/Components/SpriteRenderer.h"
#include "Engine/Core/Scripting/Prefab.h"
#include "Engine/Utility/Utility.h"

namespace Core
{
    Entity::Entity(String name)
    {
        m_guid = Utility::GenerateGUID();
        m_name = name;

        m_bounds = Rectangle();
    }

    Entity::~Entity()
    {
        RemoveAllComponents();
    }

    void Entity::Initialize()
    {
        for (UInt i = 0; i < m_components.size(); i++)
        {
            m_components[i]->Initialize();
        }
    }

    void Entity::Update(float delta)
    {
        // Update Bounds
        Vector2 worldPosition = GetTransform().GetWorldPosition();
        m_bounds.X = GetTransform().Position.X;
        m_bounds.Y = GetTransform().Position.Y;

        for (UInt i = 0; i < m_components.size(); i++)
        {
            Component& component = *m_components[i];
            if (component.IsActive())
            {
                component.Update(delta);
            }
        }

        // Update Children
        Array<Transform*> children = m_transform->GetChildren();
        for (UInt i = 0; i < children.size(); i++)
        {
            children[i]->GetOwner().Update(delta);
        }
    }

    void Entity::Render(Renderer& renderer)
    {
        for (UInt i = 0; i < m_components.size(); i++)
        {
            Component& component = *m_components[i];
            if (component.IsActive())
            {
                component.Render(renderer);
            }
        }

        // Render Children
        Array<Transform*> children = m_transform->GetChildren();
        for (UInt i = 0; i < children.size(); i++)
        {
            children[i]->GetOwner().Render(renderer);
        }
    }

    void Entity::RemoveAllComponents()
    {
        for(UInt i = 0; i < m_components.size(); i++)
        {
            m_components[i].reset();
        }

        m_components.clear();
    }

    void Entity::SetName(const String& name)
    {
        m_name = name;
        m_prefab = &God::GetPrefab(name);
    }

    Component& Entity::AddTransform()
    {
        m_transform = &AddComponent<Transform>();
        return *m_transform;
    }

    void Entity::AddTransformL(LState* L)
    {
        m_transform = &AddComponent<Transform>();

        LRef ent = getGlobal(L, "Entities");
        ent[m_guid]["Transform"] = m_transform;
    }

    void Entity::AddRenderer(LState* L)
    {
        SpriteRenderer* renderer = &AddComponent<SpriteRenderer>();

        LRef ent = getGlobal(L, "Entities");
        ent[m_guid]["Renderer"] = renderer;
    }

    void Entity::AddTag(const String& tag)
    {
        // Check if Tag already exists
        for (UInt i = 0; i < m_tags.size(); i++)
        {
            if (m_tags[i] == tag)
                return;
        }

        m_tags.push_back(tag);
    }

    void Entity::RemoveTag(const String& tag)
    {
        for (UInt i = 0; i < m_tags.size(); i++)
        {
            if (m_tags[i] == tag)
                m_tags.erase(m_tags.begin() + i);
        }
    }

    bool Entity::HasTag(const String& tag) const
    {
        for (UInt i = 0; i < m_tags.size(); i++)
        {
            if (m_tags[i] == tag)
                return true;
        }

        return false;
    }

    void Entity::SetupEmbedding(lua_State* L)
    {
        using namespace luabridge;

        BindClass<Entity>(L);
        BindProperty<Entity>(L, "name", &Entity::GetName);
        BindProperty<Entity>(L, "GUID", &Entity::GetGUID);

        BindFunction<Entity>(L, "SetName", &Entity::SetName);
        BindFunction<Entity>(L, "AddTransform", &Entity::AddTransformL);
        BindFunction<Entity>(L, "AddRenderer", &Entity::AddRenderer);
        BindFunction<Entity>(L, "AddTag", &Entity::AddTag);
        BindFunction<Entity>(L, "RemoveTag", &Entity::RemoveTag);
        BindFunction<Entity>(L, "HasTag", &Entity::HasTag);

        BindClass<SpriteRenderer>(L);
        BindFunction<SpriteRenderer>(L, "SetFrame", &SpriteRenderer::SetSpriteFrame);
    }
}
