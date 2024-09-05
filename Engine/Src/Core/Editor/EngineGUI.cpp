#include "Engine/Core/Editor/EngineGUI.h"
#include <iostream>
#include "Engine/Core/Window.h"
#include "Engine/Core/Editor/Windows/GUIWindow_EntityInfo.h"
#include "Engine/Core/Systems/EntityManager.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/Systems/StateSystem.h"
#include "Engine/Core/Renderer.h"
#include "Engine/States/GameState.h"

namespace Core::Editor
{
    EngineGUI::EngineGUI(Window& window, StateSystem& stateSystem, Input& input) : m_window(window), m_stateSystem(stateSystem), m_input(input)
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

        io.IniFilename = nullptr;

        // Create GUI Windows
        m_windows.push_back(std::make_unique<GUIWindow_EntityInfo>(*this));

        // Setup Callbacks
        Input::OnMouseLeftClick.AddListener(std::bind(&EngineGUI::DisplayEntityInfo, this));
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
        Vector2F mousePosition = Input::GetMousePosition();
        EntityManager& entityManager = static_cast<States::GameState&>(m_stateSystem.GetCurrentState()).GetEntityManager();

        Entity* highlightedEntity = entityManager.GetEntityAtPoint(mousePosition);
        if (highlightedEntity != nullptr)
        {
            if (HasClickedWithinWindow())
                return;

            if (m_pEntity == nullptr || m_pEntity != highlightedEntity)
            {
                if (m_windows[0]->IsWindowActive())
                    m_windows[0]->CloseWindow();

                m_pEntity = highlightedEntity;

                m_windows[0]->OpenWindow();
            }
        }
        else
        {
            if (!HasClickedWithinWindow())
            {
                m_windows[0]->CloseWindow();
                m_pEntity = nullptr;
            }
        }
    }

    bool EngineGUI::HasClickedWithinWindow() const
    {
        ImVec2 mousePos = ImGui::GetMousePos();

        ImVec2 windowPos = m_windows[0]->GetWindowPosition();
        ImVec2 windowSize = m_windows[0]->GetWindowSize();
        ImVec2 windowMin = windowPos;
        ImVec2 windowMax = ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y);

        return (mousePos.x >= windowMin.x && mousePos.x <= windowMax.x && mousePos.y >= windowMin.y && mousePos.y <= windowMax.y);
    }
}
