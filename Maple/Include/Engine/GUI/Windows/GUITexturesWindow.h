#pragma once
#include "GUIWindow.h"

namespace MapleEngine
{
	class Texture2D;

	class GUITexturesWindow : public GUIWindow
	{
	private:
		Texture2D* m_selectedTexture;
		int m_selectedIndex;

	public:
		GUITexturesWindow();
		~GUITexturesWindow();

		// Inherited via GUIWindow
		void RenderWindow() override;

	private:
		void DrawTextureWindow();

		ImTextureID GetTextureID(Texture2D& texture);
	};
}