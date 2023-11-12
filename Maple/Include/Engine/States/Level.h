#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Engine/Entities/Entity.h"
#include <map> 

namespace MapleEngine
{
	class ENGINE_API Level
	{
	private:
		std::map<UInt, SharedPtr<Entity>> m_entities;

	public:
		Level();
		~Level();

		virtual void InitializeLevel() = 0;
		virtual void Update(float dt);
		virtual void Render();

		template<typename T, typename... Args>
		T& CreateEntity(Args&&... args)
		{
			// Get random ID for Entity
			UInt ID = GetNewID();

			static_assert(std::is_base_of<Entity, T>::value, "T must be a subclass of Entity");
			m_entities.insert(std::make_pair(ID, std::make_shared<T>(ID, std::forward<Args>(args)...)));

			return *std::dynamic_pointer_cast<T>(m_entities[ID]);
		}

		Entity* GetEntityByID(UInt ID);
		void DestroyEntity(Entity& entity);

	private:
		/* Will return a new ID for an Entity to use. */
		UInt GetNewID();
	};
}