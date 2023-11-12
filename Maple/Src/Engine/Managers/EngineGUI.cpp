#include "Engine/Managers/EngineGUI.h"
#include "Engine/Main/Window.h"
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

MapleEngine::EngineGUI::EngineGUI(Window& window)
{
	// Initializes ImGui and sets the Style
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	//ImGui::StyleColorsDark();

	// Setup backends
	ImGui_ImplSDL2_InitForSDLRenderer(&window.GetWindow(), &window.GetRenderer());
	ImGui_ImplSDLRenderer2_Init(&window.GetRenderer());
}

MapleEngine::EngineGUI::~EngineGUI()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void MapleEngine::EngineGUI::Render()
{
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Panel");
	ImGui::Text("Hello World");
	ImGui::End();

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
