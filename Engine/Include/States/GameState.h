#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Systems/StateSystem.h"

namespace Scene { class LevelManager; class World; }

namespace Graphics { class TileMap; }

namespace Core
{
    namespace States
    {
        class GameState final : public Systems::State
        {
        private:
            UniquePtr<Scene::LevelManager> m_pLevelManager;
            UniquePtr<Scene::World> m_pWorld;
            UniquePtr<Graphics::TileMap> m_pTileMap;

        public:
            GameState();
            ~GameState() override;

            void Setup() override;
            void Initialise() override;
            void Update(float delta) override;

            Scene::World& GetWorld() const { return *m_pWorld; }
        };
    }
}

#endif //GAMESTATE_H
