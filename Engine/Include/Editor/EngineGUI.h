#ifndef ENGINEGUI_H
#define ENGINEGUI_H

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <memory>
#include <vector>

namespace Scene { class Entity; }

namespace Core
{
    namespace Systems { class StateSystem; }

    class Window;
    class Renderer;
    class Input;

    using namespace Systems;
    namespace Editor
    {
        class GUIWindow;

        class EngineGUI
        {
        private:
            Window& m_window;
            StateSystem& m_stateSystem;
            Input& m_input;

            std::vector<std::unique_ptr<GUIWindow>> m_windows;

            Scene::Entity* m_pEntity{};

        public:
            EngineGUI(Window& window, StateSystem& stateSystem, Input& input);
            ~EngineGUI();

            void Update(float delta) const;
            void Render() const;

            void RenderImGui(const Renderer& renderer);
            void HandleInput(const SDL_Event& event);

            Scene::Entity& GetSelectedEntity() const;

            Window& GetEngineWindow() const { return m_window; }

        private:
            void DisplayMenuBar() const;
            void DisplayEntityInfo();

            bool HasClickedWithinWindow() const;
        };
    }
}

#endif //ENGINEGUI_H
