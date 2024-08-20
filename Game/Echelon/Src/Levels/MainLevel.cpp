#include "Levels/MainLevel.h"

#include "Entities/BlankCharacter.h"
#include "Entities/PlayerCharacter.h"
#include "Utility/Constants.h"
#include "Utility/Utility.h"

using namespace Engine;
namespace Echelon::Levels
{
    MainLevel::MainLevel()
    {
        m_pPlayer = &CreateEntity<PlayerCharacter>();

        CreateEntity<BlankCharacter>(GetRandomPositionOnScreen());
        CreateEntity<BlankCharacter>(GetRandomPositionOnScreen());
        CreateEntity<BlankCharacter>(GetRandomPositionOnScreen());
    }

    void MainLevel::Initialize()
    {
        Level::Initialize();
    }

    void MainLevel::Update(float delta)
    {
        Level::Update(delta);
    }

    void MainLevel::Render(Renderer& renderer)
    {
        Level::Render(renderer);
    }

    Vector2 MainLevel::GetRandomPositionOnScreen()
    {
        Random rand;

        int randomXPos = rand.GetInt(0, SCREEN_WIDTH - 32);
        int randomYPos = rand.GetInt(0, SCREEN_HEIGHT - 32);
        return Vector2(randomXPos, randomYPos);
    }
}
