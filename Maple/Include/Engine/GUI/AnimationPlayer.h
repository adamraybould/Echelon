#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Engine/Graphics/Animation.h"

namespace MapleEngine
{
	class ENGINE_API AnimationPlayer
	{
	public:
		const Animation* CurrentAnimation;

	private:
		float m_animationSpeed;

		int m_frame;
		int m_frameCounter = 1; // Counts from 1
		float m_frameTimer;

	public:
		AnimationPlayer();
		AnimationPlayer(Animation* animation);
		~AnimationPlayer();

		void Update(float dt);

		void SetAnimation(Animation& animation);
		void SetAnimationSpeed(float speed) { m_animationSpeed = speed; }

		int GetCurrentFrame() { return m_frame; }
		int GetFrameCounter() { return m_frameCounter; }
		float GetFrameTimer() { return m_frameTimer; }

		float GetAnimationSpeed() { return m_animationSpeed; }
	};
}