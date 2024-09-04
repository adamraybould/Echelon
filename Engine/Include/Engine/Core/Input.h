#ifndef INPUT_H
#define INPUT_H
#include "Engine/Utility/Delegates.h"
#include "Scripting/IBinder.h"
#include "Engine/Utility/Commons.h"

union SDL_Event;

namespace Core
{
    class Input final : public IBinder
    {
    public:
        static MultiCastEvent<> OnMouseLeftClick;
        static MultiCastEvent<> OnMouseRightClick;

    private:
        static UnorderedMap<int, bool> m_keys;

    public:
        Input() = default;
        ~Input() override;

        void SetupEmbedding(lua_State* L) override;

        void ProcessInput(const SDL_Event& event);
        void ProcessMouseInput(const SDL_Event& event);

        static bool IsKeyDown(LState* L, int key);
        static bool IsKeyPressed(LState* L, int key);

        static Vector2 GetMousePosition();
    };
}

#endif //INPUT_H
