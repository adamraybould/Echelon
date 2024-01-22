#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Engine/Managers/EntityManager.h"
#include <map> 

namespace MapleEngine
{
	class ENGINE_API Level
	{
	private:
		UniquePtr<EntityManager> m_entityManager;

	public:
		Level();
		~Level();

		virtual void InitializeLevel() = 0;
		virtual void Update(float dt);
		virtual void Render();

		template<typename T, typename... Args>
		inline T& CreateEntity(Vector2 position, float rotation, Vector2 scale, Args&&... args)
		{
			T& entity = CreateEntity<T>(std::forward<Args>(args)...);
			entity.Transform.Position = position;
			entity.Transform.Rotation = rotation;
			entity.Transform.Scale = scale;
			return entity;
		}

		template<typename T, typename... Args>
		inline T& CreateEntity(Args&&... args) { return m_entityManager->CreateEntity<T>(args...); }

		void DestroyEntity(Entity& entity);

	private:
		/* Will return a new ID for an Entity to use. */
		UInt GetNewID();
	};
}