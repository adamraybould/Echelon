#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "Utility/Commons.h"

union SDL_Event;

namespace Engine::Systems
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
    };

    class InputManager
    {
    private:
        static Map<Keys, KeyState> m_keyStates;
        static Map<int, KeyState> m_mouseStates;

    public:
        InputManager();
        ~InputManager();

        void HandleInput(SDL_Event& event);

        /* Returns if a Key is Pressed */
        static bool IsKeyDown(Keys key);
    };
}

#endif //INPUTMANAGER_H
