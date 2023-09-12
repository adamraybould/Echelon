#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Components/Component.h"
#include "Engine/Utils/Commons.h"
#include <vector>
#include <iostream>

namespace MapleEngine
{
	class ENGINE_API Entity
	{
	public:
		Transform Transform;

	private:
		std::vector<Component*> m_components;

		UInt m_ID; // Unique ID for the Entity

	public:
		Entity(UInt ID);
		~Entity();

		virtual void Update(float dt);
		virtual void Render();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
			T* component = new T(std::forward<Args>(args)...);
			m_components.push_back(component);

			return *component;
		}

		template<typename T>
		T* GetComponent()
		{
			for (auto i = m_components.begin(); i != m_components.end(); i++)
			{
				T* component = dynamic_cast<T*>(*i);
				if (component != nullptr)
				{
					return component;
				}
			}

			std::cout << "Unable to find Component: " << typeid(T).name() << std::endl;
			return nullptr;
		}

		template<typename T>
		void RemoveComponent()
		{
			for (auto i = m_components.begin(); i != m_components.end(); i++)
			{
				if (dynamic_cast<T*>(i->get()) != nullptr)
				{
					m_components.erase(i);
					return;
				}
			}
		}
		
		void RemoveAllComponents();

		/* Get ID of the Entity */
		UInt& GetID() { return m_ID; }
	};
}