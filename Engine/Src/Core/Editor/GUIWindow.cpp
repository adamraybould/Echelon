#include "Engine/Core/Editor/GUIWindow.h"

namespace Core
{
    namespace Editor
    {
        void GUIWindow::PrintText(const char* str, const bool center)
        {
            if (center)
            {
                ImVec2 windowSize = ImGui::GetWindowSize();
                ImVec2 textSize = ImGui::CalcTextSize(str);

                ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
            }

            ImGui::Text(str);
        }
    }
}