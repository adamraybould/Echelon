#pragma once
#include <Engine/Entities/Components/Component.h>
#include <Engine/Entities/Components/Animator.h>

using namespace MapleEngine;
namespace Echelon
{
	class PlayerMovement : public MapleEngine::Component
	{
	private:
		SpriteRenderer* m_spriteRenderer;
		Animator* m_animator;

		Vector2 m_velocity;
		float m_movementSpeed;

	public:
		PlayerMovement(MapleEngine::Entity& entity);

		void Initialize() override;
		void Update(float dt) override;
		void Render() override;
		void Destroy() override;
	};
}