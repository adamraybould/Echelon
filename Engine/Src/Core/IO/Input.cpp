#include "Core/IO/Input.h"
#include <SDL2/SDL.h>

#include "Core/Camera.h"
#include "Core//Maths/MathF.h"

namespace Core
{
    MultiCastEvent<> Input::OnMouseLeftClick;
    MultiCastEvent<> Input::OnMouseRightClick;

    UnorderedMap<int, bool> Input::m_keys;
    float Input::m_mouseWheel;

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

    void Input::ProcessMouseInput(const SDL_Event& event)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                OnMouseLeftClick.Broadcast();
            }

            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                OnMouseRightClick.Broadcast();
            }
        }

        // Mouse Wheel
        if (event.type == SDL_MOUSEWHEEL)
        {
            m_mouseWheel = MathF::Clamp(event.wheel.y, -1.0, 1.0);
        }
    }

    void Input::Reset()
    {
        m_mouseWheel = 0.0f;
    }

    bool Input::IsKeyDown(LState* L, int key)
    {
        return m_keys[key] || m_keys[SDL_SCANCODE_TO_KEYCODE(key)];
    }

    bool Input::IsKeyPressed(LState* L, const int key)
    {
        bool isKeyDown = IsKeyDown(L, key);
        return isKeyDown == true && m_keys[key] == false;
    }

    Vector2F Input::GetMousePosition()
    {
        int x = 0;
        int y = 0;
        SDL_GetMouseState(&x, &y);

        return Camera::Main->CalculateWorldPosition(Vector2F(x, y));
    }
}
