#pragma once
#include <SDL.h>

namespace MapleEngine
{
	class Window;
	class Texture2D;

	class EngineGUI
	{
	public:
		EngineGUI(Window& window);
		~EngineGUI();

		void Render();
		void RenderDrawData();
		void HandleInput(SDL_Event& event);

		void Test(Texture2D* texture);

	private:
		void RenderMainGUI();
	};
}