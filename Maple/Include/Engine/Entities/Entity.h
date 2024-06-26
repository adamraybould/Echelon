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
		std::vector<SharedPtr<Component>> m_components;

		UInt64 m_ID; // Unique ID for the Entity

	public:
		Entity(UInt64 ID);
		~Entity();

		virtual void Update(float dt);
		virtual void Render();

		template<typename T, typename... Args>
		inline T& AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
			m_components.push_back(std::make_shared<T>(std::forward<Args>(args)...));

			return *std::dynamic_pointer_cast<T>(m_components.back());
		}

		template<typename T>
		inline T* GetComponent()
		{
			for (auto i = m_components.begin(); i != m_components.end(); i++)
			{
				T* component = std::dynamic_pointer_cast<T>(*i).get();
				if (component != nullptr)
				{
					return component;
				}
			}

			std::cout << "Unable to find Component: " << typeid(T).name() << std::endl;
			return nullptr;
		}

		template<typename T>
		inline void RemoveComponent()
		{
			for (auto i = m_components.begin(); i != m_components.end(); i++)
			{
				T* component = std::dynamic_pointer_cast<T>(*i).get();
				if (component != nullptr)
				{
					m_components.erase(i);
					return;
				}
			}
		}
		
		void RemoveAllComponents();

		/* Get ID of the Entity */
		UInt64& GetID() { return m_ID; }
	};
}