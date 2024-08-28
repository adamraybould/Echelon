#ifndef INPUT_H
#define INPUT_H
#include "Scripting/IBinder.h"

union SDL_Event;

namespace Core
{
    class Input final : public IBinder
    {
    private:
        static UnorderedMap<int, bool> m_keys;

    public:
        Input();
        ~Input() override;

        void SetupEmbedding(lua_State* L) override;

        void ProcessInput(const SDL_Event& event);

        static bool IsKeyDown(LState* L, int key);
        static bool IsKeyPressed(LState* L, int key);
    };
}

#endif //INPUT_H
