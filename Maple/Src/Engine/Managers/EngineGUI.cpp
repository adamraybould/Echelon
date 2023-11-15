#include "Engine/Managers/EngineGUI.h"
#include "Engine/Main/Window.h"
#include <iostream>
#include "Engine/Graphics/Texture2D.h"
#include "Engine/Managers/AssetManager.h"

MapleEngine::EngineGUI::EngineGUI(Window& window)
{
	// Initializes ImGui and sets the Style
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();

	// Setup backends
	ImGui_ImplSDL2_InitForSDLRenderer(&window.GetWindow(), &window.GetRenderer());
	ImGui_ImplSDLRenderer2_Init(&window.GetRenderer());

	float m_frameTimer = 0.0f;
	float m_animationSpeed = 100;
	m_spriteSheetMenuOpen = false;
}

MapleEngine::EngineGUI::~EngineGUI()
{
	//Clear All Animation Players
	ClearAnimationPlayers();

	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void MapleEngine::EngineGUI::Update(float dt)
{
	// If one of the Sprite Sheet menus are open, update the animation players
	if (m_spriteSheetMenuOpen)
	{
		for (auto i = m_GUIAnimationPlayers.begin(); i != m_GUIAnimationPlayers.end(); i++)
		{
			i->second->UpdateAnimationPlayers(dt);
		}
	}
}

void MapleEngine::EngineGUI::Render()
{
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	RenderMainGUI();

	ImGui::Render();
}

void MapleEngine::EngineGUI::RenderDrawData()
{
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void MapleEngine::EngineGUI::HandleInput(SDL_Event& event)
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}

void MapleEngine::EngineGUI::RenderMainGUI()
{
	if (ImGui::Begin("Inspector"))
	{
		if (ImGui::CollapsingHeader("Assets"))
		{
			if (ImGui::TreeNode("Loaded Textures"))
			{
				std::vector<UniquePtr<Texture2D>>& loadedTextures = AssetManager::GetLoadedTextures();
				for (int i = 0; i < loadedTextures.size(); i++)
				{
					if (ImGui::TreeNode(loadedTextures[i]->GetTexturePath().c_str()))
					{
						Texture2D& texture = *loadedTextures[i];
						std::string sizeText = "Size: " + std::to_string(texture.GetTextureMemorySize()) + "KB";
						ImGui::Text(sizeText.c_str());

						ImGui::Separator();
	
						ImGui::Image(GetTextureID(texture), ImVec2(texture.GetWidth(), texture.GetHeight()));
						ImGui::TreePop();
					}
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Loaded Sprite Sheets"))
			{
				std::map<std::string, UniquePtr<SpriteSheet>>& loadedSpriteSheets = AssetManager::GetLoadedSpriteSheets();
				for (auto i = loadedSpriteSheets.begin(); i != loadedSpriteSheets.end(); i++)
				{
					std::string spriteSheetName = i->first;
					SpriteSheet& spriteSheet = *i->second;
					CreateAnimationPlayer(spriteSheetName, spriteSheet);
					m_spriteSheetMenuOpen = true;

					if (ImGui::TreeNode(spriteSheetName.c_str()))
					{
						Texture2D& texture = i->second->GetTextureAtlas();
						ImGui::Image(GetTextureID(texture), ImVec2(texture.GetWidth(), texture.GetHeight()));

						ImGui::Separator();

						std::map<std::string, Animation> animations = i->second->GetAllAnimations();
						for (auto j = animations.begin(); j != animations.end(); j++)
						{
							std::string animationName = j->first;
							ImGui::Text(animationName.c_str());

							ImGui::Separator();

							AnimationPlayer& animationPlayer = m_GUIAnimationPlayers[spriteSheetName]->GetAnimationPlayer(animationName);
							int frame = animationPlayer.GetCurrentFrame();
							int frameCount = animationPlayer.CurrentAnimation->GetFrameCount();
							int frameCounter = animationPlayer.GetFrameCounter();

							int maxXIndex = texture.GetWidth() / spriteSheet.GetSpriteWidth();
							int xFramePos = (animationPlayer.GetCurrentFrame() % maxXIndex) * spriteSheet.GetSpriteWidth();
							int yFrameIndex = (int)(frame / maxXIndex);
							int yFramePos = yFrameIndex * spriteSheet.GetSpriteHeight();

							ImVec2 frameOrigin = ImVec2(xFramePos / (float)texture.GetWidth(), yFramePos / (float)texture.GetHeight());
							ImVec2 frameSize = ImVec2((xFramePos + spriteSheet.GetSpriteWidth()) / (float)texture.GetWidth(), (yFramePos + spriteSheet.GetSpriteHeight()) / (float)texture.GetHeight());
							
							ImGui::Text("Current Frame: %i", frameCounter);
							ImGui::Text("Frame Count: %i", frameCount);

							int animationSpeed = animationPlayer.GetAnimationSpeed();
							ImGui::SliderInt("Animation Speed", &animationSpeed, 0, 200);
							animationPlayer.SetAnimationSpeed(animationSpeed);

							ImGui::Image(GetTextureID(texture), ImVec2(spriteSheet.GetSpriteWidth() * 4, spriteSheet.GetSpriteHeight() * 4), frameOrigin, frameSize);
							
						}

						ImGui::TreePop();
					}
				}

				ImGui::TreePop();
			}
			else
			{
				m_spriteSheetMenuOpen = false;
				// Will clear all the Animation Players if the Menu is closed
				ClearAnimationPlayers();
			}
		}

		ImGui::End();
	}
}

ImTextureID MapleEngine::EngineGUI::GetTextureID(Texture2D& texture)
{
	return (ImTextureID)(intptr_t)&texture.GetRawTexture();
}


void MapleEngine::EngineGUI::CreateAnimationPlayer(std::string ID, SpriteSheet& spriteSheet)
{
	if (m_GUIAnimationPlayers.find(ID) == m_GUIAnimationPlayers.end())
	{
		UniquePtr<GUIAnimationPlayer> player = std::make_unique<GUIAnimationPlayer>(spriteSheet);
		m_GUIAnimationPlayers.insert(std::make_pair(ID, std::move(player)));
	}
}

void MapleEngine::EngineGUI::ClearAnimationPlayers()
{
	for (auto i = m_GUIAnimationPlayers.begin(); i != m_GUIAnimationPlayers.end(); i++)
	{
		i->second.reset();
	}
	m_GUIAnimationPlayers.clear();
}
