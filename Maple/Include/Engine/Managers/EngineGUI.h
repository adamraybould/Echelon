#pragma once
#include <SDL.h>

namespace MapleEngine
{
	class Window;

	class EngineGUI
	{
	public:
		EngineGUI(Window& window);
		~EngineGUI();

		void Render();
		void RenderDrawData();
		void HandleInput(SDL_Event& event);

	private:
		void RenderMainGUI();
	};
}