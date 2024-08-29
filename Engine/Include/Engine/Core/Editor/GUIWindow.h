#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include "Engine/Core/Editor/EngineGUI.h"

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
    };
}

#endif //GUIWINDOW_H