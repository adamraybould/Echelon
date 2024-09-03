#include "Engine/Core/Editor/GUIWindow.h"

namespace Core
{
    namespace Editor
    {
        void GUIWindow::PrintText(const char* str, const bool center, const bool partOfColumn)
        {
            if (center)
            {
                int width = partOfColumn == false ? ImGui::GetWindowWidth() : ImGui::GetColumnWidth();
                int textWidth = ImGui::CalcTextSize(str).x;

                ImGui::SetCursorPosX((width - textWidth) * 0.5f);
            }

            ImGui::TextUnformatted(str);
        }

        void GUIWindow::PrintHoverText(const String& title, const String& str)
        {
            std::string truncatedStr = str.substr(0, 8) + "...";

            String titleStr = title + "%s";
            ImGui::Text(titleStr.c_str(), truncatedStr.c_str());

            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("%s", str.c_str());
            }
        }
    }
}