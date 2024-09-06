#ifndef GUIWINDOW_H
#define GUIWINDOW_H
#include "Editor/EngineGUI.h"
#include "Core/TypeDefs.h"

namespace Core::Editor
{
    struct GUIWindow
    {
    protected:
        EngineGUI& m_engineGUI;
        bool m_isActive = false;

    public:
        GUIWindow(EngineGUI& engineGUI) : m_engineGUI(engineGUI) {}
        virtual ~GUIWindow() = default;

        virtual void OpenWindow() { m_isActive = true; }
        virtual void CloseWindow() { m_isActive = false; }

        virtual void Update(float delta) = 0;
        virtual void Render() = 0;

        void SetActive(const bool value) { m_isActive = value; }
        bool IsWindowActive() const { return m_isActive; }

        virtual ImVec2 GetWindowPosition() = 0;
        virtual ImVec2 GetWindowSize() = 0;

    protected:
        void PrintText(const String& str, bool center = false, bool partOfColumn = false);
        void PrintHoverText(const String& title, const String& str);
    };
}

#endif //GUIWINDOW_H
