#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Engine/Graphics/Animation.h"
#include "Engine/Graphics/SpriteSheet.h"
#include <map>

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

	struct GUIAnimationPlayer
	{
	private:
		SpriteSheet& m_spriteSheet;

		bool m_loaded;
		std::map<std::string, UniquePtr<AnimationPlayer>> m_animationPlayers;

	public:
		GUIAnimationPlayer(SpriteSheet& spriteSheet) : m_spriteSheet(spriteSheet)
		{
			m_loaded = false;

			// Create Animation Players
			std::map<std::string, Animation>& animations = spriteSheet.GetAllAnimations();
			for (auto i = animations.begin(); i != animations.end(); i++)
			{
				UniquePtr<AnimationPlayer> player = std::make_unique<AnimationPlayer>(&i->second);
				m_animationPlayers.insert(std::make_pair(i->first, std::move(player)));
			}

			m_loaded = true;
		}

		void UpdateAnimationPlayers(float dt)
		{
			for (auto i = m_animationPlayers.begin(); i != m_animationPlayers.end(); i++)
			{
				i->second->Update(dt);
			}
		}

		AnimationPlayer& GetAnimationPlayer(std::string name)
		{
			return *m_animationPlayers[name];
		}
	};
}