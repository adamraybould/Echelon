#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Engine/Core/Systems/StateSystem.h"

namespace Core
{
    namespace Systems
    {
        class EntityManager;
        class LevelManager;
    }

    namespace Graphics { class TileMap; }

    using namespace Systems;
    using namespace Graphics;
    namespace States
    {
        class GameState final : public State
        {
        private:
            UniquePtr<EntityManager> m_pEntityManager;
            UniquePtr<LevelManager> m_pLevelManager;

            UniquePtr<TileMap> m_pTileMap;

        public:
            GameState();
            ~GameState() override;

            void Initialize() override;
            void Update(float delta) override;
            void Render(Renderer& renderer) override;

            EntityManager& GetEntityManager() const { return *m_pEntityManager; }
            LevelManager& GetLevelManager() const { return *m_pLevelManager; }
        };
    }
}

#endif //GAMESTATE_H
