#pragma once
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <string>
#include <map>
#include "Engine/Utils/Commons.h"
#include "AnimationPlayer.h"
#include "Engine/Graphics/SpriteSheet.h"

#include "Windows/GUITexturesWindow.h"

namespace MapleEngine
{
	class Window;
	class Texture2D;

	class EngineGUI
	{
	private:
		std::vector<GUIWindow*> m_windows;

		bool m_menuActive;
		bool m_texturesMenuActive;

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