#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Engine/Entities/Entity.h"
#include "Engine/Utils/ProjectUtils.h"
#include "Engine/Utils/Commons.h"
#include <map>

namespace MapleEngine
{
	class ENGINE_API EntityManager
	{
	private:
		std::map<UInt64, SharedPtr<Entity>> m_entities;

	public:
		EntityManager();
		~EntityManager();

		template<typename T, typename... Args>
		inline T& CreateEntity(Args&&... args)
		{
			// Ensures the type is an Entity
			static_assert(std::is_base_of<Entity, T>::value, "T must be a subclass of Entity");

			UInt64 uniqueID = ProjectUtils::GenerateUniqueID();
			SharedPtr<Entity> entity = std::make_shared<T>(uniqueID, std::forward<Args>(args)...);

			m_entities.insert(std::make_pair(uniqueID, entity));
			return *std::dynamic_pointer_cast<T>(entity);
		}

		void DeleteEntity(UInt64 ID);

		/* Returns an Entity with the specified ID */
		Entity* GetEntity(UInt64 ID);

		/* Returns the Map of Entities */
		std::map<UInt64, SharedPtr<Entity>>& GetEntityMap() { return m_entities; }
	};
}