#ifndef GUIWINDOW_H
#define GUIWINDOW_H
#include "Editor/EngineGUI.h"
#include "Core/TypeDefs.h"
#include "Core/Maths/Vector2.h"

namespace Core
{
    namespace Editor
    {
        class GUIWindow
        {
        private:
            Vector2F m_windowPosition;
            Vector2U m_windowSize;

        protected:
            EngineGUI& m_engineGUI;
            bool m_isActive = false;

        public:
            GUIWindow(EngineGUI& engineGUI) : m_engineGUI(engineGUI) { m_isActive = false; }
            virtual ~GUIWindow() = default;

            virtual void OpenWindow() { m_isActive = true; }
            virtual void CloseWindow() { m_isActive = false; }

            virtual void Update(float delta) = 0;
            virtual void Render() = 0;

            void SetActive(const bool value) { m_isActive = value; }
            bool IsWindowActive() const { return m_isActive; }

            void SetWindowPosition(const Vector2F pos) { m_windowPosition = pos; ImGui::SetNextWindowPos(ToVec2(m_windowPosition), ImGuiCond_None); }
            Vector2F& GetWindowPosition () { return m_windowPosition; }

            void SetWindowSize(const Vector2U size) { m_windowSize = size; ImGui::SetNextWindowSize(ToVec2(size), ImGuiCond_None);}
            Vector2U& GetWindowSize() { return m_windowSize; }

        protected:
            void PrintText(const String& str, bool center = false, bool partOfColumn = false);
            void PrintHoverText(const String& title, const String& str);

            static ImVec2 ToVec2(const Vector2F& vec) { return { vec.X, vec.Y }; }
        };
    }
}

#endif //GUIWINDOW_H
