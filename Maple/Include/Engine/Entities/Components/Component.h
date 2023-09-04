#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace MapleEngine
{
	class Entity;

	class ENGINE_API Component
	{
	private:
		Entity& m_rOwner;
		bool m_isActive;

	public:
		Component(Entity& entity);

		virtual void Initialize() = 0;
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;
		virtual void Destroy() = 0;

		/* Returns the Owner of the Component */
		Entity& GetOwner() { return m_rOwner; }

		/* Set the Component to be active or not */
		void SetActive(bool active) { m_isActive = active; }
		/* Returns if the Component is active */
		bool IsActive() { return m_isActive; }
	};
}