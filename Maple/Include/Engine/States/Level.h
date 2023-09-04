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
	class Level
	{
	private:
		std::map<UInt, Entity*> m_entities;

	public:
		Level();
		~Level();

		virtual void InitializeLevel() = 0;
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;

		template<typename T>
		T& CreateEntity()
		{
			// Get random ID for Entity
			UInt ID = GetNewID();

			static_assert(std::is_base_of<Entity, T>::value, "T must be a subclass of Entity");
			T* entity = new T(ID);

			Entity& baseEntity = dynamic_cast<Entity&>(*entity);
			m_entities.insert(std::make_pair(ID, entity));

			return *entity;
		}

		Entity* GetEntityByID(UInt ID);
		void DestroyEntity(Entity& entity);

	private:
		/* Will return a new ID for an Entity to use. */
		UInt GetNewID();
	};
}