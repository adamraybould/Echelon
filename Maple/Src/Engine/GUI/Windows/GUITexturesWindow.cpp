#include "Engine/GUI/Windows/GUITexturesWindow.h"
#include "Engine/Graphics/Texture2D.h"
#include "Engine/Managers/AssetManager.h"
#include "Engine/Utils/MathF.h"

MapleEngine::GUITexturesWindow::GUITexturesWindow()
{
	m_selectedTexture = nullptr;
	m_selectedIndex = 0;
}

MapleEngine::GUITexturesWindow::~GUITexturesWindow()
{

}

void MapleEngine::GUITexturesWindow::RenderWindow()
{
	if (!m_active)
		return;

	if (ImGui::Begin("Textures", &m_active, ImGuiWindowFlags_MenuBar))
	{	
		std::vector<UniquePtr<Texture2D>>& loadedTextures = AssetManager::GetLoadedTextures();
		if (ImGui::BeginListBox(" ", ImVec2(250, 400)))
		{	
			if (m_selectedTexture == nullptr)
				m_selectedTexture = loadedTextures[0].get();

			for (int i = 0; i < loadedTextures.size(); i++)
			{
				const bool isSelected = (m_selectedIndex == i);
				if (ImGui::Selectable(loadedTextures[i]->GetTexturePath().c_str(), isSelected))
				{
					m_selectedIndex = i;
					m_selectedTexture = loadedTextures[i].get();
				}

				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndListBox();
		}

		DrawTextureWindow();

		ImGui::End();
	}
	else
	{
		ImGui::End();
	}
}

void MapleEngine::GUITexturesWindow::DrawTextureWindow()
{
	ImGui::SameLine();
	
	if (m_selectedTexture != nullptr)
	{
		int displayWidth = fmin(m_selectedTexture->GetWidth(), 400);
		int displayHeight = fmin(m_selectedTexture->GetHeight(), 400);
		ImGui::Image(GetTextureID(*m_selectedTexture), ImVec2(displayWidth, displayHeight));

		ImGui::Separator();

		std::string sizeText = "Size: " + std::to_string(m_selectedTexture->GetTextureMemorySize()) + "KB";
		ImGui::Text(sizeText.c_str());
	}
}

ImTextureID MapleEngine::GUITexturesWindow::GetTextureID(Texture2D& texture)
{
	return (ImTextureID)(intptr_t)&texture.GetRawTexture();
}
