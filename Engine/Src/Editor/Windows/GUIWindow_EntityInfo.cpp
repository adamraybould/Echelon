#include "Editor/Windows/GUIWindow_EntityInfo.h"

#include <imgui.h>
#include <iostream>
#include <cctype>
#include <GL/glew.h>

#include "Core/IO/Window.h"
#include "Scene/Entities/Components/SpriteRenderer.h"
#include "Core/IO/Renderer.h"
#include "Core/Camera.h"
#include "Scene/Entities/Components/Animator.h"
#include "Core/Scripting/Prefab.h"
#include "Core/Constants.h"
#include "Core/Maths/MathF.h"
#include "Core/Utility.h"
#include "Graphics/Material.h"
#include "Graphics/Sprite.h"

using namespace Scene;
using namespace Scene::Components;
namespace Core
{
    namespace Editor
    {
        GUIWindow_EntityInfo::GUIWindow_EntityInfo(EngineGUI& engineGUI) : GUIWindow(engineGUI)
        {
            SetWindowSize(Vector2U(350, 250));
            m_windowOffset = Vector2F(GetWindowSize().X * 0.1f, GetWindowSize().Y * 1.2f);
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

            m_pEntity = nullptr;
            m_windowDistance = 0;
        }

        void GUIWindow_EntityInfo::Update(float delta)
        {
            if (m_windowDistance >= MAX_WINDOW_DISTANCE)
            {
                CloseWindow();
            }
        }

        void GUIWindow_EntityInfo::Render()
        {
            if (m_pEntity == nullptr)
                return;

            Camera& camera = m_engineGUI.GetEngineWindow().GetRenderer().GetCamera();
            float zoom = camera.GetZoom();
            zoom = MathF::Clamp(zoom, 0.5f, 1.0f);

            const Vector2F entityPos = m_pEntity->GetTransform().GetWorldPosition();
            const Vector2F windowPos = camera.CalculateScreenPosition(entityPos);
            m_windowDistance = (camera.GetCameraPosition() - windowPos).Length() * zoom;

            // Set Position and Size of Window
            SetWindowPosition(Vector2F(windowPos.X, windowPos.Y));
            SetWindowSize(Vector2U(GetWindowSize().X + m_windowExpansionWidth, GetWindowSize().Y + m_windowExpansionHeight));

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

        Vector2F GUIWindow_EntityInfo::GetEntityScreenPosition(const Entity& entity) const
        {
            const Camera& camera = m_engineGUI.GetEngineWindow().GetRenderer().GetCamera();
            return camera.CalculateScreenPosition(entity.GetTransform().GetWorldPosition());
        }

        void GUIWindow_EntityInfo::DisplayInfo(const Entity& entity)
        {
            const String prefabName = Utility::Capitalize(entity.GetName());
            const String guid = entity.GetGUID();

            const Vector2F entityWorldPosition = entity.GetTransform().GetWorldPosition();

            const UInt childWidth = GetWindowSize().X;
            const float childHeight = 100 + (m_pEntityRenderer->GetDisplaySource().Height * 0.2f);

            if (ImGui::BeginChild("Info", ImVec2(childWidth, childHeight), false))
            {
                ImGui::Columns(2, nullptr, true);
                ImGui::SetColumnWidth(0, GetWindowSize().X * 0.6f);

                PrintHoverText("Guid: ", guid);
                ImGui::Text("Prefab: %s", prefabName.c_str());
                ImGui::Text("Position: (%d, %d)", static_cast<int>(entityWorldPosition.X), static_cast<int>(entityWorldPosition.Y));

                DisplayTags();

                ImGui::NextColumn();

                DisplaySprite();
            }

            ImGui::EndChild();
        }

        void GUIWindow_EntityInfo::DisplaySprite() const
        {
            if (m_pEntitySprite == nullptr)
                return;

            const UInt textureWidth = m_pEntitySprite->GetWidth();
            const UInt textureHeight = m_pEntitySprite->GetHeight();

            constexpr float desiredWidth = 80.0f;
            const float desiredHeight = desiredWidth / m_pEntityRenderer->GetDisplaySource().Width * m_pEntityRenderer->GetDisplaySource().Height;

            const RectF spriteSource = m_pEntityRenderer->GetDisplaySource();
            const ImVec2 uv0 = ImVec2(static_cast<float>(spriteSource.X) / textureWidth, static_cast<float>(spriteSource.Y) / textureHeight);
            const ImVec2 uv1 = ImVec2(static_cast<float>(spriteSource.X + spriteSource.Width) / textureWidth, static_cast<float>(spriteSource.Y + spriteSource.Height) / textureHeight);

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
            ImGui::Image((void*)(intptr_t)m_pEntitySprite->GetMaterial().GetTexture(), ImVec2(desiredWidth, desiredHeight), uv0, uv1);

            // Display current animation if playing
            if (m_pEntity->HasComponent<Animator>())
            {
                const Animator& animator = *m_pEntity->GetComponent<Animator>();
                const String currentAnimName = animator.GetCurrentAnimation().Name;

                const float width = ImGui::GetColumnWidth();
                const float textWidth = ImGui::CalcTextSize(currentAnimName.c_str()).x;

                const float centerX = (width - textWidth) * 0.35f;
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
                const LRef entityRef = getGlobal(ScriptCore::Instance()->GetLuaState(), "Entities")[m_pEntity->GetGUID()];
                const LRef raceRef = entityRef["components"]["race"];
                if (!raceRef.isNil())
                {
                    ImGui::Text("Race: %s", raceRef["race"].tostring().c_str());
                }

                // Health Component
                const LRef healthRef = entityRef["components"]["health"];
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

            if (ImGui::TreeNode("Tags"))
            {
                const Array<String>& tags = m_pEntity->GetTags();
                constexpr int columnWidth = 2;
                const int rowCount = (tags.size() + columnWidth - 1) / columnWidth;

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

                ImGui::TreePop();
            }
        }
    }
}
