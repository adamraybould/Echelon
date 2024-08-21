#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Engine/Systems/StateSystem.h"

namespace Core::Systems
{
    class LevelManager;
}

namespace Core::States
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
        void Render(Renderer& renderer) override;
    };
}

#endif //GAMESTATE_H
