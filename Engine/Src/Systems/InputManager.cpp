#include "Systems/InputManager.h"

#include <iostream>
#include <SDL.h>

#include "Utility/MathF.h"

namespace Engine::Systems
{
    Map<Keys, KeyState> InputManager::m_keyStates;
    Map<int, KeyState> InputManager::m_mouseStates;
    float InputManager::m_mouseWheel;

    Map<SDL_Keycode, Keys> keyMap =
    {
        { NULL,		Keys::NULLKEY },
        { SDLK_a,		Keys::A },
        { SDLK_b,		Keys::B },
        { SDLK_c,		Keys::C },
        { SDLK_d,		Keys::D },
        { SDLK_e,		Keys::E },
        { SDLK_f,		Keys::F },
        { SDLK_g,		Keys::G },
        { SDLK_h,		Keys::H },
        { SDLK_i,		Keys::I },
        { SDLK_j,		Keys::J },
        { SDLK_k,		Keys::K },
        { SDLK_l,		Keys::L },
        { SDLK_m,		Keys::M },
        { SDLK_n,		Keys::N },
        { SDLK_o,		Keys::O },
        { SDLK_p,		Keys::P },
        { SDLK_q,		Keys::Q },
        { SDLK_r,		Keys::R },
        { SDLK_s,		Keys::S },
        { SDLK_t,		Keys::T },
        { SDLK_u,		Keys::U },
        { SDLK_v,		Keys::V },
        { SDLK_w,		Keys::W },
        { SDLK_x,		    Keys::X },
        { SDLK_y,		  Keys::Y },
        { SDLK_z,		Keys::Z },
        { SDLK_0,		Keys::N0 },
        { SDLK_1,		Keys::N1 },
        { SDLK_2,		Keys::N2 },
        { SDLK_3,		Keys::N3 },
        { SDLK_4,		Keys::N4 },
        { SDLK_5,		Keys::N5 },
        { SDLK_6,		Keys::N6 },
        { SDLK_7,		Keys::N7 },
        { SDLK_8,		Keys::N8 },
        { SDLK_9,		Keys::N9 },
        { SDLK_0,		Keys::N0 },
        { SDLK_F1,		Keys::F1 },
        { SDLK_F2,		Keys::F2 },
        { SDLK_F3,		Keys::F3 },
        { SDLK_F4,		Keys::F4 },
        { SDLK_F5,		Keys::F5 },
        { SDLK_F6,		Keys::F6 },
        { SDLK_F7,		Keys::F7 },
        { SDLK_F8,		Keys::F8 },
        { SDLK_F9,		Keys::F9 },
        { SDLK_F10,	Keys::F10 },
        { SDLK_F11,	Keys::F11 },
        { SDLK_F12,	Keys::F12 },
        { SDLK_LSHIFT,	Keys::SHIFT },
        { SDLK_SPACE,	Keys::SPACE },
        { SDLK_LCTRL,	Keys::CTRL },
        { SDLK_LALT,	Keys::ALT },
        { SDLK_TAB,     Keys::TAB },
        { SDLK_AC_BACK, Keys::BACK },
        { SDLK_ESCAPE,  Keys::ESC },
        { SDLK_UP, Keys::UP },
        { SDLK_DOWN, Keys::DOWN },
        { SDLK_LEFT, Keys::LEFT },
        { SDLK_RIGHT, Keys::RIGHT },
    };

    InputManager::InputManager()
    {
        for (auto i = keyMap.begin(); i != keyMap.end(); i++)
        {
            Keys key = i->second;
            m_keyStates.insert(std::make_pair(key, KeyState::KEY_UP));
        }
    }

    InputManager::~InputManager()
    {
        m_keyStates.clear();
        m_mouseStates.clear();
    }

    void InputManager::HandleInput(SDL_Event& event)
    {
        Keys key = keyMap[event.key.keysym.sym];

        if (SDL_KEYDOWN == event.type)
            m_keyStates[key] = KeyState::KEY_DOWN;

        if (SDL_KEYUP == event.type)
            m_keyStates[key] = KeyState::KEY_UP;

        HandleMouse(event);
    }

    void InputManager::HandleMouse(SDL_Event& event)
    {
        if (event.type == SDL_MOUSEWHEEL)
        {
            m_mouseWheel = MathF::Clamp(event.wheel.y, -1.0, 1.0);
        }
    }

    void InputManager::Reset()
    {
        m_mouseWheel = 0.0f;
    }

    bool InputManager::IsKeyDown(Keys key)
    {
        return m_keyStates[key] == KeyState::KEY_DOWN;
    }
}
