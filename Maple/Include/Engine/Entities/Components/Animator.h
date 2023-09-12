#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Component.h"
#include "Engine/Entities/Components/SpriteRenderer.h"
#include "Engine/Graphics/SpriteSheet.h"
#include "Engine/Graphics/Animation.h"

namespace MapleEngine
{
	class ENGINE_API Animator : public Component
	{
	public:
		const Animation* CurrentAnimation;

	private:
		SpriteRenderer& m_rSpriteRenderer;
		SpriteSheet& m_rSpriteSheet;

		float m_speed; // Animation Speed

		int m_frame;
		float m_frameTimer;

	public:
		Animator(Entity& entity, SpriteRenderer& spriteRenderer, SpriteSheet& spriteSheet);

		// Inherited via Component
		void Initialize() override;
		void Update(float dt) override;
		void Render() override;
		void Destroy() override;

		/* Sets a new Animation to be played */
		void SetAnimation(const char* name);

		void SetAnimationSpeed(const float speed) { m_speed = speed; }
		int GetAnimationSpeed() const { return m_speed; }
	};
}