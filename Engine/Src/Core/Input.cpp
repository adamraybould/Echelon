#include "Engine/Core/Input.h"
#include <SDL.h>

namespace Core
{
    UnorderedMap<int, bool> Input::m_keys;

    Input::Input()
    = default;

    Input::~Input()
    {
        m_keys.clear();
    }

    void Input::SetupEmbedding(lua_State* L)
    {
        BindStaticFunction(L, "Input", "IsKeyDown", &Input::IsKeyDown);
        BindStaticFunction(L, "Input", "IsKeyPressed", &Input::IsKeyPressed);
    }

    void Input::ProcessInput(const SDL_Event& event)
    {
        SDL_Keycode key = event.key.keysym.sym;
        if (SDL_KEYDOWN == event.type)
        {
            m_keys[key] = true;
        }

        if (SDL_KEYUP == event.type)
        {
            m_keys[key] = false;
        }
    }

    bool Input::IsKeyDown(LState* L, const int key)
    {
        return m_keys[key] || m_keys[SDL_SCANCODE_TO_KEYCODE(key)];
    }

    bool Input::IsKeyPressed(LState* L, int key)
    {
        bool isKeyDown = IsKeyDown(L, key);
        return isKeyDown == true && m_keys[key] == false;
    }
}
