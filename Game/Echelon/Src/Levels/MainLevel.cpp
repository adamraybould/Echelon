#include "Levels/MainLevel.h"

#include "Entities/BlankCharacter.h"
#include "Entities/PlayerCharacter.h"
#include "Entities/Components/CameraFollow.h"
#include "Rendering/Camera.h"
#include "Utility/Constants.h"
#include "Utility/Utility.h"

using namespace Engine;
namespace Echelon::Levels
{
    MainLevel::MainLevel()
    {
        //Vector2 centerPosition = Vector2((SCREEN_WIDTH / 2) - 32, (SCREEN_HEIGHT / 2) - 32);
        m_pPlayer = &Instantiate<PlayerCharacter>();

        BlankCharacter& blank1 = Instantiate<BlankCharacter>(GetRandomPositionOnScreen());
        BlankCharacter& blank2 = Instantiate<BlankCharacter>(GetRandomPositionOnScreen());
        BlankCharacter& blank3 = Instantiate<BlankCharacter>(GetRandomPositionOnScreen());

        Camera::Main()->AddComponent<CameraFollow>(*m_pPlayer);
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

        int randomXPos = rand.GetInt(-500, 500);
        int randomYPos = rand.GetInt(-500, 500);
        return Vector2(randomXPos, randomYPos);
    }
}
