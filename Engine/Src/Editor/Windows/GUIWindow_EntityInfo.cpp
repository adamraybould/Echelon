#include "Editor/Windows/GUIWindow_EntityInfo.h"

#include <imgui.h>
#include <iostream>
#include <cctype>

#include "Core/IO/Window.h"
#include "Scene/Entities/Components/SpriteRenderer.h"
#include "Core/IO/Renderer.h"
#include "Core/Camera.h"
#include "Scene/Entities/Components/Animator.h"
#include "Core/Scripting/Prefab.h"
#include "Core/Constants.h"
#include "Core/Maths/MathF.h"
#include "Core/Utility.h"

namespace Core::Editor
{
    GUIWindow_EntityInfo::GUIWindow_EntityInfo(EngineGUI& engineGUI) : GUIWindow(engineGUI)
    {
        m_isActive = false;

        m_offsetX = WINDOW_WIDTH * 0.1f;
        m_offsetY = WINDOW_HEIGHT * 1.2f;
    }

    void GUIWindow_EntityInfo::OpenWindow()
    {
        GUIWindow::OpenWindow();

        m_pEntity = &m_engineGUI.GetSelectedEntity();
        SpriteRenderer* spriteRenderer = m_pEntity->GetComponent<SpriteRenderer>();
        if (spriteRenderer != nullptr)
        {
            m_pEntityRenderer = spriteRenderer;
            m_pEntitySprite = &spriteRenderer->GetSprite();
        }
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

        Camera& camera = m_engineGUI.GetEngineWindow().GetRenderer().GetCamera();
        float zoom = camera.GetZoom();
        zoom = MathF::Clamp(zoom, 0.5f, 1.0f);

        Vector2I offsetFromCamera = Vector2I(m_pEntity->GetTransform().Position.X - camera.GetCameraOrigin().X, m_pEntity->GetTransform().Position.Y - camera.GetCameraOrigin().Y);

        // Adjust window position based on zoom
        Vector2I windowOffset = Vector2I(offsetFromCamera.X + (SCREEN_WIDTH * 0.5f) + m_offsetX, offsetFromCamera.Y + (SCREEN_HEIGHT * 0.5f) - m_offsetY);

        m_windowPos = ImVec2(windowOffset.X * zoom, windowOffset.Y * zoom);
        ImGui::SetNextWindowPos(m_windowPos, ImGuiCond_Always);

        ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH + m_windowExpansionWidth, WINDOW_HEIGHT + m_windowExpansionHeight), ImGuiCond_Always);

        if (ImGui::Begin("Entity Info", &m_isActive, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
        {
            DisplayInfo(*m_pEntity);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            DisplayComponentInfo();

            ImGui::End();
        }
    }

    ImVec2 GUIWindow_EntityInfo::GetWindowPosition()
    {
        return m_windowPos;
    }

    ImVec2 GUIWindow_EntityInfo::GetWindowSize()
    {
        return ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    Vector2F GUIWindow_EntityInfo::GetEntityScreenPosition(const Entity& entity) const
    {
        Camera& camera = m_engineGUI.GetEngineWindow().GetRenderer().GetCamera();
        return camera.CalculateScreenPosition(entity.GetTransform().GetWorldPosition());
    }

    void GUIWindow_EntityInfo::DisplayInfo(const Entity& entity)
    {
        String prefabName = Utility::Capitalize(entity.GetName());
        String guid = entity.GetGUID();

        Vector2F entityWorldPosition = entity.GetTransform().GetWorldPosition();

        float childWidth = WINDOW_WIDTH;
        float childHeight = 100 + (m_pEntityRenderer->GetDisplaySource().Height * 0.2f);

        if (ImGui::BeginChild("Info", ImVec2(childWidth, childHeight), false))
        {
            ImGui::Columns(2, nullptr, true);
            ImGui::SetColumnWidth(0, WINDOW_WIDTH * 0.6f);

            PrintHoverText("Guid: ", guid);
            //ImGui::Text("GUID: %s", entity.GetGUID().c_str());

            ImGui::Text("Prefab: %s", prefabName.c_str());
            ImGui::Text("Position: (%d, %d)", static_cast<int>(entityWorldPosition.X), static_cast<int>(entityWorldPosition.Y));

            DisplayTags();

            ImGui::NextColumn();

            DisplaySprite();

            ImGui::EndChild();
        }
    }

    void GUIWindow_EntityInfo::DisplaySprite()
    {
        if (m_pEntitySprite == nullptr)
            return;

        UInt textureWidth = m_pEntitySprite->GetWidth();
        UInt textureHeight = m_pEntitySprite->GetHeight();

        float desiredWidth = 80.0f;
        float desiredHeight = desiredWidth / m_pEntityRenderer->GetDisplaySource().Width * m_pEntityRenderer->GetDisplaySource().Height;

        RectI spriteSource = m_pEntityRenderer->GetDisplaySource();
        ImVec2 uv0 = ImVec2(static_cast<float>(spriteSource.X) / textureWidth, static_cast<float>(spriteSource.Y) / textureHeight);
        ImVec2 uv1 = ImVec2(static_cast<float>(spriteSource.X + spriteSource.Width) / textureWidth, static_cast<float>(spriteSource.Y + spriteSource.Height) / textureHeight);

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
        ImGui::Image(GetTextureID(*m_pEntitySprite), ImVec2(desiredWidth, desiredHeight), uv0, uv1);

        // Display current animation if playing
        if (m_pEntity->HasComponent<Animator>())
        {
            Animator& animator = *m_pEntity->GetComponent<Animator>();
            String currentAnimName = animator.GetCurrentAnimation().Name;

            float width = ImGui::GetColumnWidth();
            float textWidth = ImGui::CalcTextSize(currentAnimName.c_str()).x;

            float centerX = (width - textWidth) * 0.35f;
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + centerX);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 15.0f);

            ImGui::TextUnformatted(currentAnimName.c_str());
        }
    }

    void GUIWindow_EntityInfo::DisplayComponentInfo() const
    {
        if (m_pEntity->HasPrefab())
        {
            // Race Component
            LRef entityRef = luabridge::getGlobal(ScriptCore::Instance()->GetLuaState(), "Entities")[m_pEntity->GetGUID()];
            LRef raceRef = entityRef["components"]["race"];
            if (!raceRef.isNil())
            {
                ImGui::Text("Race: %s", raceRef["race"].tostring().c_str());
            }

            // Health Component
            LRef healthRef = entityRef["components"]["health"];
            if (!healthRef.isNil())
            {
                ImGui::Text("Health: %s", healthRef["currenthealth"].tostring().c_str());
            }
        }
    }

    void GUIWindow_EntityInfo::DisplayTags() const
    {
        if (m_pEntity == nullptr)
            return;

        int initialHeight = ImGui::GetCursorPosY();

        if (ImGui::TreeNode("Tags"))
        {
            Array<String>& tags = m_pEntity->GetTags();
            int columnWidth = 2;
            int rowCount = (tags.size() + columnWidth - 1) / columnWidth;

            if (ImGui::BeginTable("tags", columnWidth))
            {
                for (int row = 0; row < rowCount; ++row)
                {
                    ImGui::TableNextRow();

                    for (int column = 0; column < columnWidth; column++)
                    {
                        int index = row * columnWidth + column;

                        if (index < tags.size())
                        {
                            ImGui::TableSetColumnIndex(column);
                            ImGui::BulletText("%s", tags[index].c_str());
                        }
                        else
                        {
                            ImGui::TableSetColumnIndex(column);
                        }
                    }
                }

                ImGui::EndTable();
            }

            //float newHeight = ImGui::GetCursorPosY() - initialHeight;
            //m_windowExpansionHeight = newHeight;

            ImGui::TreePop();
        }
    }
}