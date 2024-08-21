#ifndef MAINLEVEL_H
#define MAINLEVEL_H
#include "Entities/PlayerCharacter.h"
#include "States/Level.h"

namespace Engine::Rendering
{
    class Camera;
}

using namespace Engine::Rendering;
using namespace Engine::States;
using namespace Echelon::Entities;
namespace Echelon::Levels
{
    class MainLevel : public Level
    {
    private:
        PlayerCharacter* m_pPlayer;

    public:
        MainLevel();

        void Initialize() override;
        void Update(float delta) override;
        void Render(Renderer& renderer) override;

        Vector2 GetRandomPositionOnScreen();
    };
}

#endif //MAINLEVEL_H
