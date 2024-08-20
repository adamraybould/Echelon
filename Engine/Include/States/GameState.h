#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Systems/StateSystem.h"

namespace Engine::Systems
{
    class LevelManager;
}

namespace Engine::States
{
    class GameState : public Systems::State
    {
    private:
        UniquePtr<Systems::LevelManager> m_pLevelManager;

    public:
        GameState();
        ~GameState() override;

        void Initialize() override;
        void Update(float delta) override;
        void Render(SDL_Renderer& renderer) override;
    };
}

#endif //GAMESTATE_H
