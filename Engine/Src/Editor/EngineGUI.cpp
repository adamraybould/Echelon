#include "Editor/EngineGUI.h"

#include <iostream>
#include "imgui_impl_opengl3.h"

#include "Core/IO/Window.h"
#include "Editor/Windows/GUIWindow_EntityInfo.h"
#include "Systems/EntityManager.h"
#include "Core/IO/Input.h"
#include "Systems/StateSystem.h"
#include "Core/IO/Renderer.h"
#include "States/GameState.h"

namespace Core::Editor
{
    EngineGUI::EngineGUI(Window& window, StateSystem& stateSystem, Input& input) : m_window(window), m_stateSystem(stateSystem), m_input(input)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = nullptr;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(&window.GetWindow(), window.GetContext());
        ImGui_ImplOpenGL3_Init("#version 450");

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

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void EngineGUI::Update(const float delta) const
    {
        for (UInt i = 0; i < m_windows.size(); i++)
        {
            if (m_windows[i] == nullptr || !m_windows[i]->IsWindowActive())
                continue;

            m_windows[i]->Update(delta);
        }
    }

    void EngineGUI::Render() const
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        DisplayMenuBar();

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
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void EngineGUI::HandleInput(const SDL_Event& event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }

    Entity& EngineGUI::GetSelectedEntity() const
    {
        return *m_pEntity;
    }

    void EngineGUI::DisplayMenuBar() const
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Options"))
            {
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void EngineGUI::DisplayEntityInfo()
    {
        const Vector2F mousePosition = Input::GetMousePosition();
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
        const ImVec2 mousePos = ImGui::GetMousePos();

        const Vector2F& windowPos = m_windows[0]->GetWindowPosition();
        const Vector2U& windowSize = m_windows[0]->GetWindowSize();

        const Vector2F& min = windowPos;
        const Vector2F max = Vector2F(windowPos.X + windowSize.X, windowPos.Y + windowSize.Y);

        return mousePos.x >= min.X && mousePos.x <= max.X && mousePos.y >= min.Y && mousePos.y <= max.Y;
    }
}
