#pragma once
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

namespace MapleEngine
{
	struct GUIWindow
	{
	protected:
		bool m_active; // Is the Window Active?

	public:
		void OpenWindow() { m_active = true; }
		void CloseWindow() { m_active = false; }

		virtual void RenderWindow() = 0;
	};
}