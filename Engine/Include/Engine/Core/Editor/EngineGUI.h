#ifndef ENGINEGUI_H
#define ENGINEGUI_H

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <memory>
#include <vector>

namespace Core
{
    namespace Systems { class StateSystem; class InputManager; }

    class Window;
    class Renderer;
    class Entity;

    using namespace Systems;
    namespace Editor
    {
        class GUIWindow;

        class EngineGUI
        {
        private:
            Window& m_window;
            StateSystem& m_stateSystem;
            InputManager& m_inputManager;

            std::vector<std::unique_ptr<GUIWindow>> m_windows;

            Entity* m_pEntity;

        public:
            EngineGUI(Window& window, StateSystem& stateSystem, InputManager& inputManager);
            ~EngineGUI();

            void Update(float delta) const;
            void Render(Renderer& renderer) const;

            void RenderImGui(const Renderer& renderer);
            void HandleInput(const SDL_Event& event);

            Entity& GetSelectedEntity() const;

            Window& GetEngineWindow() const { return m_window; }

        private:
            void RenderMenuBar() const;
            void DisplayEntityInfo();

            bool HasClickedWithinWindow() const;
        };
    }
}

#endif //ENGINEGUI_H
