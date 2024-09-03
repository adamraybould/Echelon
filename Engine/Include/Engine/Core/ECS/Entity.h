#ifndef ENTITY_H
#define ENTITY_H
#include "Engine/Core/Scripting/IBinder.h"
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Engine/Core/Interfaces/IRenderable.h"

using namespace Core::Components;
namespace Core
{
    namespace Scripting { class Prefab; }

    using namespace Scripting;
    class Entity : public IBinder, public IRenderable
    {
    private:
        Prefab* m_prefab = nullptr;

        GUID m_guid;
        String m_name;

        Rectangle m_bounds;

        Array<UniquePtr<Component>> m_components;
        Array<String> m_tags;

    protected:
        Transform* m_transform;

    public:
        Entity(const String& name);
        virtual ~Entity();

        virtual void Initialize();
        virtual void Update(float delta);
        void Render(Renderer& renderer) override;

        void RemoveAllComponents();

        void SetBounds(const Rectangle rect) { m_bounds = rect; }
        Rectangle GetBounds() const { return m_bounds; }

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

        Transform& GetTransform() const { return *m_transform; }

        void AddTag(const String& tag);
        void RemoveTag(const String& tag);
        bool HasTag(const String& tag) const;
        Array<String>& GetTags() { return m_tags; }

        void SetupEmbedding(lua_State* L) override;

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

        float GetDepth() override
        {
            if (m_transform != nullptr)
            {
                return m_transform->Position.Y;
            }

            return 0.0f;
        }
    };
}

using namespace Core;
#endif //ENTITY_H
