#include "Engine/Core/Editor/Windows/GUIWindow_EntityInfo.h"

#include <imgui.h>

#include "Engine/Core/Window.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/ECS/Components/SpriteRenderer.h"
#include "../../../../Include/Engine/Core/Renderer.h"
#include "../../../../Include/Engine/Core/Camera.h"

namespace Core::Editor
{
    GUIWindow_EntityInfo::GUIWindow_EntityInfo(EngineGUI& engineGUI) : GUIWindow(engineGUI)
    {
        m_isActive = false;
    }

    void GUIWindow_EntityInfo::OpenWindow()
    {
        GUIWindow::OpenWindow();

        m_pEntity = &m_engineGUI.GetSelectedEntity();
        SpriteRenderer* spriteRenderer = m_pEntity->GetComponent<SpriteRenderer>();
        if (spriteRenderer != nullptr)
        {
            m_pEntitySprite = &spriteRenderer->GetSprite();
        }

        Vector2 entityScreenPosition = GetEntityScreenPosition(*m_pEntity);
        m_position = entityScreenPosition;
    }

    void GUIWindow_EntityInfo::CloseWindow()
    {
        GUIWindow::CloseWindow();
    }

    void GUIWindow_EntityInfo::Update(float delta)
    {
    }

    void GUIWindow_EntityInfo::Render()
    {
        if (m_pEntity == nullptr)
            return;

        int offsetX = WINDOW_WIDTH * 0.5f;
        int offsetY = WINDOW_HEIGHT * 0.8f;

        ImVec2 windowPos = ImVec2(m_position.X + offsetX, m_position.Y - offsetY);
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT), ImGuiCond_Once);

        Vector2 entityWorldPosition = m_pEntity->GetTransform().GetWorldPosition();
        std::string positionText = "(" + std::to_string(entityWorldPosition.X) + ", " + std::to_string(entityWorldPosition.Y) + ")";

        if (ImGui::Begin("Entity Info", &m_isActive, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
        {
            ImGui::Text("ID: %u", m_pEntity->GetID());
            ImGui::Text("Name: %s", m_pEntity->GetName());
            ImGui::Text("Position: (%.1f, %1.f)", entityWorldPosition.X, entityWorldPosition.Y);

            ImGui::Spacing();
            ImGui::Separator();

            if (m_pEntitySprite != nullptr)
            {
                int textureWidth = m_pEntitySprite->GetWidth();
                int textureHeight = m_pEntitySprite->GetHeight();

                float desiredWidth = 100.0f;
                float desiredHeight = (desiredWidth / m_pEntitySprite->GetSource().Width) * m_pEntitySprite->GetSource().Height;

                Rectangle spriteSource = m_pEntitySprite->GetSource();
                ImVec2 uv0 = ImVec2(spriteSource.X / textureWidth, spriteSource.Y / textureHeight);
                ImVec2 uv1 = ImVec2((spriteSource.X + spriteSource.Width) / textureWidth, (spriteSource.Y + spriteSource.Height) / textureHeight);

                float posX = (WINDOW_WIDTH - desiredWidth) * 0.5f;
                float posY = (WINDOW_HEIGHT - desiredHeight) * 0.7f;

                // Set the cursor position to the calculated position
                ImGui::SetCursorPos(ImVec2(posX, posY));

                ImGui::Image(GetTextureID(*m_pEntitySprite), ImVec2(desiredWidth, desiredHeight), uv0, uv1);
            }

            ImGui::End();
        }
    }

    Vector2 GUIWindow_EntityInfo::GetEntityScreenPosition(const Entity& entity)
    {
        Camera& camera = m_engineGUI.GetEngineWindow().GetRenderer().GetCamera();
        return camera.CalculateScreenPosition(entity.GetTransform().GetWorldPosition());
    }
}
