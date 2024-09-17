#include "Scene/Entities/Entity.h"
#include "Core/Scripting/Engine.h"
#include "Core/IO/Renderer.h"
#include "Scene/Entities/Components/Animator.h"
#include "Scene/Entities/Components/Rigidbody.h"
#include "Scene/Entities/Components/SpriteRenderer.h"
#include "Scene/Entities/Components/SoundEmitter.h"
#include "Core/Scripting/Prefab.h"
#include "Core/Utility.h"
#include "Scene/Entities/Components/LightSource.h"
#include "Scene/Entities/Components/ParticleSystem.h"

namespace Scene
{
    Entity::Entity(const String& name)
    {
        m_guid = Utility::GenerateGUID();
        m_name = name;
    }

    Entity::~Entity()
    {
        RemoveAllComponents();
    }

    void Entity::SetupEmbedding(lua_State* L)
    {
        using namespace luabridge;

        BindClass<Entity>(L);
        BindProperty<Entity>(L, "name", &Entity::GetName);
        BindProperty<Entity>(L, "GUID", &Entity::GetGUID);
        //BindFunction<Entity>(L, "SetRenderLayer", &IRenderable::SetRenderLayer);

        BindFunction<Entity>(L, "AddTransform", &Entity::AddTransform);
        BindFunction<Entity>(L, "AddRenderer", &Entity::AddRenderer);
        BindFunction<Entity>(L, "AddRigidbody", &Entity::AddRigidbody);
        BindFunction<Entity>(L, "AddAnimator", &Entity::AddAnimator);
        BindFunction<Entity>(L, "AddSoundEmitter", &Entity::AddSoundEmitter);
        BindFunction<Entity>(L, "AddParticleSystem", &Entity::AddParticleSystem);
        BindFunction<Entity>(L, "AddLightSource", &Entity::AddLightSource);

        BindFunction<Entity>(L, "SetName", &Entity::SetName);
        BindFunction<Entity>(L, "AddTag", &Entity::AddTag);
        BindFunction<Entity>(L, "RemoveTag", &Entity::RemoveTag);
        BindFunction<Entity>(L, "HasTag", &Entity::HasTag);

        BindClass<SpriteRenderer>(L);
        BindClass<Rigidbody>(L);
        BindClass<Animator>(L);
        BindClass<SoundEmitter>(L);
        BindClass<ParticleSystem>(L);
        BindClass<LightSource>(L);
    }

    void Entity::Initialize()
    {
        for (UInt i = 0; i < m_components.size(); i++)
        {
            m_components[i]->Initialize();
        }

        CallFunction("OnEntityWake", m_guid);
    }

    void Entity::Update(const float delta)
    {
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
        m_prefab = &Engine::GetPrefab(name);
    }

    void Entity::AddTransform(LState* L)
    {
        m_transform = &AddComponent<Transform>();

        if (L != nullptr)
        {
            m_transform->SetupEmbedding(L);
            RegisterComponent<Transform>(L, m_transform, "Transform");
        }
    }

    void Entity::AddRenderer(LState* L)
    {
        SpriteRenderer* renderer = &AddComponent<SpriteRenderer>();
        renderer->SetupEmbedding(L);

        RegisterComponent<SpriteRenderer>(L, renderer, "Renderer");
    }

    void Entity::AddRigidbody(LState* L)
    {
        Rigidbody* rigidbody = &AddComponent<Rigidbody>();
        rigidbody->SetupEmbedding(L);

        RegisterComponent<Rigidbody>(L, rigidbody, "Rigidbody");
    }

    void Entity::AddAnimator(LState* L)
    {
        Animator* animator = &AddComponent<Animator>();
        animator->SetupEmbedding(L);

        RegisterComponent<Animator>(L, animator, "Animator");
    }

    void Entity::AddSoundEmitter(LState* L)
    {
        SoundEmitter* soundEmitter = &AddComponent<SoundEmitter>();
        soundEmitter->SetupEmbedding(L);

        RegisterComponent<SoundEmitter>(L, soundEmitter, "SoundEmitter");
    }

    void Entity::AddParticleSystem(LState* L)
    {
        ParticleSystem* particleSystem = &AddComponent<ParticleSystem>();
        particleSystem->SetupEmbedding(L);

        RegisterComponent<ParticleSystem>(L, particleSystem, "ParticleSystem");
    }

    void Entity::AddLightSource(LState* L)
    {
        LightSource* lightSource = &AddComponent<LightSource>();
        lightSource->SetupEmbedding(L);

        RegisterComponent<LightSource>(L, lightSource, "Light");
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
}
