#ifndef MAINLEVEL_H
#define MAINLEVEL_H
#include "Engine/States/Level.h"

namespace Core
{
    class Engine;
}

using namespace Core::States;
namespace Echelon::Levels
{
    class MainLevel : public Level
    {
    public:
        MainLevel(EntityManager& entityManager);
        ~MainLevel() override;

        void Initialize() override;
        void Update(float delta) override;
        void Render(Renderer& renderer) override;

        Vector2 GetRandomPositionOnScreen();
    };
}

#endif //MAINLEVEL_H
