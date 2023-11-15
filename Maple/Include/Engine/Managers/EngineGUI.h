#pragma once
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <string>
#include <map>
#include "Engine/Utils/Commons.h"
#include "Engine/GUI/AnimationPlayer.h"
#include "Engine/Graphics/SpriteSheet.h"

namespace MapleEngine
{
	class Window;
	class Texture2D;

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

	class EngineGUI
	{
	private:
		bool m_spriteSheetMenuOpen;
		int m_frame = 0;
		float m_frameTimer;
		float m_animationSpeed;
		std::map<std::string, UniquePtr<GUIAnimationPlayer>> m_GUIAnimationPlayers;

	public:
		EngineGUI(Window& window);
		~EngineGUI();

		void Update(float dt);
		void Render();
		void RenderDrawData();
		void HandleInput(SDL_Event& event);

	private:
		void RenderMainGUI();

		ImTextureID GetTextureID(Texture2D& texture);

		void CreateAnimationPlayer(std::string ID, SpriteSheet& spriteSheet);
		void ClearAnimationPlayers();
	};
}