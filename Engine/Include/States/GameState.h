#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Systems/StateSystem.h"

namespace Graphics { class TileMap; }

namespace Core
{
    namespace Systems
    {
        class EntityManager;
        class LevelManager;
    }

    namespace States
    {
        class GameState final : public Systems::State
        {
        private:
            UniquePtr<Systems::EntityManager> m_pEntityManager;
            UniquePtr<Systems::LevelManager> m_pLevelManager;

            UniquePtr<Graphics::TileMap> m_pTileMap;

        public:
            GameState();
            ~GameState() override;

            void Initialize() override;
            void Update(float delta) override;
            void Render(Renderer& renderer) override;

            Systems::EntityManager& GetEntityManager() const { return *m_pEntityManager; }
            Systems::LevelManager& GetLevelManager() const { return *m_pLevelManager; }
        };
    }
}

#endif //GAMESTATE_H
