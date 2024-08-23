#include "Engine/Core/Editor/EngineGUI.h"
#include <iostream>
#include "Engine/Core/Window.h"
#include "Engine/Core/Editor/Windows/GUIWindow_EntityInfo.h"
#include "Engine/Core/Systems/EntityManager.h"
#include "Engine/Core/Systems/InputManager.h"
#include "Engine/Core/Systems/StateSystem.h"
#include "Engine/Core/Renderer.h"
#include "Engine/States/GameState.h"

namespace Core::Editor
{
    EngineGUI::EngineGUI(Window& window, StateSystem& stateSystem, InputManager& inputManager) : m_window(window), m_stateSystem(stateSystem), m_inputManager(inputManager)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForSDLRenderer(&window.GetWindow(), window.GetRenderer());
        ImGui_ImplSDLRenderer2_Init(window.GetRenderer());

        // Create GUI Windows
        m_windows.push_back(std::make_unique<GUIWindow_EntityInfo>(*this));

        // Setup Callbacks
        InputManager::OnMouseLeftClick.AddListener(std::bind(&EngineGUI::DisplayEntityInfo, this));
    }

    EngineGUI::~EngineGUI()
    {
        for (UInt i = 0; i < m_windows.size(); i++)
        {
            m_windows[i].reset();
        }
        m_windows.clear();

        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void EngineGUI::Update(float delta) const
    {
        for (UInt i = 0; i < m_windows.size(); i++)
        {
            if (m_windows[i] == nullptr || !m_windows[i]->IsWindowActive())
                continue;

            m_windows[i]->Update(delta);
        }
    }

    void EngineGUI::Render(Renderer& renderer) const
    {
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        RenderMenuBar();

        for (UInt i = 0; i < m_windows.size(); i++)
        {
            if (m_windows[i] == nullptr || !m_windows[i]->IsWindowActive())
                continue;

            m_windows[i]->Render();
        }

        ImGui::Render();
    }

    void EngineGUI::RenderImGui(const Renderer& renderer)
    {
        renderer.ResetRenderer();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    }

    void EngineGUI::HandleInput(const SDL_Event& event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }

    Entity& EngineGUI::GetSelectedEntity() const
    {
        return *m_pEntity;
    }

    void EngineGUI::RenderMenuBar() const
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Resources"))
            {
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void EngineGUI::DisplayEntityInfo()
    {
        Vector2 mousePosition = m_inputManager.GetMousePosition();
        EntityManager& entityManager = static_cast<States::GameState&>(m_stateSystem.GetCurrentState()).GetEntityManager();

        Entity* highlightedEntity = entityManager.GetEntityAtPoint(mousePosition);
        if (highlightedEntity != nullptr)
        {
            if (m_pEntity == nullptr || m_pEntity != highlightedEntity)
            {
                if (m_windows[0]->IsWindowActive())
                    m_windows[0]->CloseWindow();

                m_pEntity = highlightedEntity;

                m_windows[0]->OpenWindow();
                std::cout << "Entity Clicked: " << highlightedEntity->GetID() << std::endl;
            }
        }
        else
        {
            m_windows[0]->CloseWindow();
            m_pEntity = nullptr;
        }
    }
}
