#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "Engine/Core/Scripting/IBinder.h"
#include "Engine/Utility/Commons.h"
#include "Engine/Utility/Delegates.h"

union SDL_Event;

namespace Core
{
    class Camera;

    namespace Systems
    {
        enum KeyState
        {
            KEY_UP,
            KEY_DOWN
        };

        enum class Keys {
            NULLKEY,
            A, B, C, D, E, F, G, H, I, J, K, L, M,
            N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            N1, N2, N3, N4, N5, N6, N7, N8, N9, N0,
            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
            SHIFT, SPACE, CTRL, ALT, TAB, BACK, ESC,
            UP, DOWN, LEFT, RIGHT,
        };

        class InputManager
        {
        public:
            static MultiCastEvent<void, void> OnMouseLeftClick;
            static MultiCastEvent<void, void> OnMouseRightClick;

        private:
            Camera& m_camera;

            static Map<Keys, KeyState> m_keyStates;
            static Map<int, KeyState> m_mouseStates;

            static float m_mouseWheel;
            static Vector2 m_currentMousePosition;

        public:
            explicit InputManager(Camera& camera);
            ~InputManager();

            void HandleInput(const SDL_Event& event);
            void HandleMouse(const SDL_Event& event);

            void Reset();

            /* Returns if a Key is Pressed */
            static bool IsKeyDown(Keys key);
            static bool IsKeyDownL(LState* L, int key);

            /* Returns the Mouse Position in World Coordinates */
            Vector2 GetMousePosition() const;

            /* Returns the Movement of the Mouse Wheel */
            static float GetMouseWheel() { return m_mouseWheel; }

        private:
            void CalculateMousePosition();

        };
    }
}

#endif //INPUTMANAGER_H
