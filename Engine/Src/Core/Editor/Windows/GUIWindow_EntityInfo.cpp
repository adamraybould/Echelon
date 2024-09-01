#include "Engine/Core/Editor/Windows/GUIWindow_EntityInfo.h"

#include <imgui.h>
#include <iostream>
#include <cctype>

#include "Engine/Core/Window.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/ECS/Components/SpriteRenderer.h"
#include "../../../../Include/Engine/Core/Renderer.h"
#include "../../../../Include/Engine/Core/Camera.h"
#include "Engine/Core/ECS/Components/Animator.h"
#include "Engine/Core/Scripting/Prefab.h"
#include "Engine/Utility/Constants.h"
#include "Engine/Utility/MathF.h"

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

        float offsetX = WINDOW_WIDTH * 0.2f;
        float offsetY = WINDOW_HEIGHT * 1.2f;

        Vector2 entityScreenPosition = GetEntityScreenPosition(*m_pEntity);
        //entityScreenPosition *= zoom;

        Vector2 offsetFromCamera((m_pEntity->GetTransform().Position.X - camera.GetPosition().X),(m_pEntity->GetTransform().Position.Y - camera.GetPosition().Y));

        // Adjust window position based on zoom
        Vector2 windowOffset = Vector2((offsetFromCamera.X) + (SCREEN_WIDTH * 0.5f) + offsetX, (offsetFromCamera.Y) + (SCREEN_HEIGHT * 0.5f) - offsetY);

        //Vector2 windowOffset = Vector2((entityScreenPosition.X / zoom) + (SCREEN_WIDTH * 0.5f) + offsetX, (entityScreenPosition.Y / zoom) + (SCREEN_HEIGHT * 0.5f) - offsetY);

        //std::cout << zoom << std::endl;

        ImVec2 windowPos = ImVec2(windowOffset.X * zoom, windowOffset.Y * zoom);
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);

        ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT), ImGuiCond_Always);

        Vector2 entityWorldPosition = m_pEntity->GetTransform().GetWorldPosition();
        std::string positionText = "(" + std::to_string(entityWorldPosition.X) + ", " + std::to_string(entityWorldPosition.Y) + ")";

        if (ImGui::Begin("Entity Info", &m_isActive, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
        {
            String prefabName = m_pEntity->GetName();
            prefabName[0] = std::toupper(prefabName[0]);

            ImGui::Text("GUID: %s", m_pEntity->GetGUID().c_str());
            ImGui::Text("Prefab: %s", prefabName.c_str());
            ImGui::Text("Position: (%.1f, %.1f)", entityWorldPosition.X, entityWorldPosition.Y);

            if (m_pEntity->HasPrefab())
            {
                LRef entityRef = luabridge::getGlobal(ScriptCore::Instance()->GetLuaState(), "Entities")[m_pEntity->GetGUID()];
                LRef healthRef = entityRef["components"]["health"];
                if (!healthRef.isNil())
                {
                    ImGui::Text("Health: %s", healthRef["health"].tostring().c_str());
                }
            }

            ImGui::Spacing();
            ImGui::Separator();

            if (m_pEntitySprite != nullptr)
            {
                int textureWidth = m_pEntitySprite->GetWidth();
                int textureHeight = m_pEntitySprite->GetHeight();

                float desiredWidth = 100.0f;
                float desiredHeight = (desiredWidth / m_pEntityRenderer->GetDisplaySource().Width) * m_pEntityRenderer->GetDisplaySource().Height;

                Rectangle spriteSource = m_pEntityRenderer->GetDisplaySource();
                ImVec2 uv0 = ImVec2(spriteSource.X / textureWidth, spriteSource.Y / textureHeight);
                ImVec2 uv1 = ImVec2((spriteSource.X + spriteSource.Width) / textureWidth, (spriteSource.Y + spriteSource.Height) / textureHeight);

                float posX = (WINDOW_WIDTH - desiredWidth) * 0.5f;
                float posY = (WINDOW_HEIGHT - desiredHeight) * 0.7f;

                // Set the cursor position to the calculated position
                ImGui::SetCursorPos(ImVec2(posX, posY));

                ImGui::Image(GetTextureID(*m_pEntitySprite), ImVec2(desiredWidth, desiredHeight), uv0, uv1);

                if (m_pEntity->HasComponent<Animator>())
                {
                    Animator& animator = *m_pEntity->GetComponent<Animator>();
                    String currentAnimName = animator.GetCurrentAnimation().Name;

                    PrintText(currentAnimName.c_str(), true);
                }
            }

            ImGui::End();
        }
    }

    Vector2 GUIWindow_EntityInfo::GetEntityScreenPosition(const Entity& entity) const
    {
        Camera& camera = m_engineGUI.GetEngineWindow().GetRenderer().GetCamera();
        return camera.CalculateScreenPosition(entity.GetTransform().GetWorldPosition());
    }
}
