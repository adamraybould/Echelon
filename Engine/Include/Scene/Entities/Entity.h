#ifndef ENTITY_H
#define ENTITY_H

#include "Core/Scripting/IBinder.h"
#include "Core/IO/IRenderable.h"

#include "Components/Component.h"
#include "Components/Transform.h"
#include "Core/Maths/Rectangle.h"

namespace Core::Scripting { class Prefab; }
using namespace Core::Scripting;

namespace Scene
{
    using namespace Scene::Components;
    class Entity : public IBinder, public IRenderable
    {
    private:
        Prefab* m_prefab = nullptr;
        Transform* m_transform;

        GUID m_guid;
        String m_name;

        RectI m_bounds;

        Array<UniquePtr<Component>> m_components;
        Array<String> m_tags;

    public:
        Entity(const String& name);
        virtual ~Entity();

        void SetupEmbedding(lua_State* L) override;

        virtual void Initialize();
        virtual void Update(float delta);
        void Render(Renderer& renderer) override;

        void RemoveAllComponents();

        void SetBounds(const RectI rect) { m_bounds = rect; }
        RectI GetBounds() const { return m_bounds; }

        Prefab& GetPrefab() const { return *m_prefab; }
        bool HasPrefab() const { return m_prefab != nullptr; }

        /* Returns the Entity GUID */
        GUID GetGUID() const { return m_guid; }

        void SetName(const String& name);
        String GetName() const { return m_name; }

        void AddTransform(LState* L);
        void AddRenderer(LState* L);
        void AddRigidbody(LState* L);
        void AddAnimator(LState* L);
        void AddSoundEmitter(LState* L);
        void AddParticleSystem(LState* L);

        Transform& GetTransform() const { return *m_transform; }

        void AddTag(const String& tag);
        void RemoveTag(const String& tag);
        bool HasTag(const String& tag) const;
        Array<String>& GetTags() { return m_tags; }

        float GetDepth() override;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of_v<Component, T>, "T must be a subclass of Component");

            UniquePtr<Component> component = std::make_unique<T>(static_cast<Entity&>(*this), std::forward<Args>(args)...);
            m_components.push_back(std::move(component));

            return *dynamic_cast<T*>(m_components.back().get());
        }

        template<typename T>
        void RemoveComponent()
        {
            static_assert(std::is_base_of_v<Component, T>, "T must be a subclass of Component");

            for (const auto& componentPtr : m_components)
            {
                T* component = dynamic_cast<T*>(componentPtr.get());
                if (component != nullptr)
                {
                    m_components.erase(component);
                    return;
                }
            }
        }

        template<typename T>
        bool HasComponent()
        {
            return GetComponent<T>() != nullptr;
        }

        template<typename T>
        T* GetComponent()
        {
            static_assert(std::is_base_of_v<Component, T>, "T must be a subclass of Component");

            for (const auto& componentPtr : m_components)
            {
                T* component = dynamic_cast<T*>(componentPtr.get());
                if (component != nullptr)
                {
                    return component;
                }
            }

            //printf("Unable to find Component: " + typeid(T).name());
            return nullptr;
        }

    private:
        template<typename T>
        void RegisterComponent(LState* L, T* component, const String& name)
        {
            static_assert(std::is_base_of_v<Component, T>, "T must be a subclass of Component");

            LRef ent = luabridge::getGlobal(L, "Entities");
            ent[m_guid][name] = component;
        }
    };
}

using namespace Core;
#endif //ENTITY_H
