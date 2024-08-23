#ifndef ENTITY_H
#define ENTITY_H
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Engine/Utility/Commons.h"

using namespace Core::Components;
namespace Core
{
    class Entity
    {
    private:
        UInt64 m_ID;
        const char* m_name;

        Rectangle m_bounds;
        Transform* m_transform;

        Array<UniquePtr<Component>> m_components;

    public:
        Entity(const char* name);
        virtual ~Entity();

        virtual void Initialize() = 0;
        virtual void Update(float delta);
        virtual void Render(Renderer& renderer);

        void RemoveAllComponents();

        void SetBounds(const Rectangle rect) { m_bounds = rect; }
        Rectangle GetBounds() const { return m_bounds; }

        UInt32 GetID() const { return m_ID; }
        const char* GetName() const { return m_name; }

        Transform& GetTransform() const { return *m_transform; }

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
    };
}

using namespace Core;
#endif //ENTITY_H
