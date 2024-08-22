#ifndef MAINLEVEL_H
#define MAINLEVEL_H
#include "Echelon/Entities/PlayerCharacter.h"
#include "Engine/States/Level.h"

namespace Core::Rendering
{
    class Camera;
}

using namespace Core::Rendering;
using namespace Core::States;
using namespace Echelon::Entities;
namespace Echelon::Levels
{
    class MainLevel : public Level
    {
    private:
        PlayerCharacter* m_pPlayer;

    public:
        MainLevel(EntityManager& entityManager);

        void Initialize() override;
        void Update(float delta) override;
        void Render(Renderer& renderer) override;

        Vector2 GetRandomPositionOnScreen();
    };
}

#endif //MAINLEVEL_H
