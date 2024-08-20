#ifndef ENTITY_H
#define ENTITY_H
#include "Components/Component.h"
#include "Utility/Commons.h"

namespace Engine::ECS
{
    class Entity
    {
    private:
        Transform m_transform;
        UInt64 m_ID;

        Array<UniquePtr<Component>> m_components;

    public:
        Entity();
        virtual ~Entity();

        virtual void Initialize() = 0;
        virtual void Update(float delta);
        virtual void Render(SDL_Renderer& renderer);

        template<typename T, typename... Args>
        inline T& AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of_v<Component, T>, "T must be a subclass of Component");

            UniquePtr<Component> component = std::make_unique<T>(std::forward<Args>(args)...);
            m_components.push_back(std::move(component));

            return *dynamic_cast<T*>(m_components.back().get());
        }

        template<typename T>
        inline void RemoveComponent()
        {
            static_assert(std::is_base_of_v<Component, T>, "T must be a subclass of Component");

            for (auto i = m_components.begin(); i != m_components.end(); ++i)
            {
                T* component = dynamic_cast<T*>(m_components.back().get());
                if (component != nullptr)
                {
                    m_components.erase(i);
                    return;
                }
            }
        }

        template<typename T>
        inline T* GetComponent()
        {
            static_assert(std::is_base_of_v<Component, T>, "T must be a subclass of Component");

            for (auto i = m_components.begin(); i != m_components.end(); ++i)
            {
                T* component = dynamic_cast<T*>(m_components.back().get());
                if (component != nullptr)
                {
                    return component;
                }
            }

            //printf("Unable to find Component: " + typeid(T).name());
            return nullptr;
        }

        void RemoveAllComponents();

        UInt32 GetID() const { return m_ID; }
        Transform& Transform() { return m_transform; }
    };
}

#endif //ENTITY_H
