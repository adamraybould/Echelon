#include "Echelon/Levels/MainLevel.h"

#include "Echelon/Entities/BlankCharacter.h"
#include "Echelon/Entities/PlayerCharacter.h"
#include "Echelon/Entities/Components/CameraFollow.h"
#include <Engine/Core/Camera.h>
#include <Engine/Utility/Utility.h>

#include "Echelon/Entities/Mobs/Drillbot.h"
#include "Echelon/Entities/Mobs/Gunbot.h"

using namespace Core;
using namespace Mobs;
namespace Echelon::Levels
{
    MainLevel::MainLevel(EntityManager& entityManager) : Level(entityManager)
    {
        //Vector2 centerPosition = Vector2((SCREEN_WIDTH / 2) - 32, (SCREEN_HEIGHT / 2) - 32);
        m_pPlayer = &Instantiate<PlayerCharacter>("Player");

        BlankCharacter& blank1 = Instantiate<BlankCharacter>("Blank", GetRandomPositionOnScreen());
        BlankCharacter& blank2 = Instantiate<BlankCharacter>("Blank", GetRandomPositionOnScreen());
        BlankCharacter& blank3 = Instantiate<BlankCharacter>("Blank", GetRandomPositionOnScreen());

        Gunbot& gunbot = Instantiate<Gunbot>("Gunbot 1.0", GetRandomPositionOnScreen());
        Drillbot& drillbot = Instantiate<Drillbot>("Drillbot 0.5", GetRandomPositionOnScreen());

        Entity* camera = Camera::Main;
        if (camera != nullptr)
            camera->AddComponent<CameraFollow>(*m_pPlayer);
    }

    void MainLevel::Initialize()
    {
    }

    void MainLevel::Update(float delta)
    {
    }

    void MainLevel::Render(Renderer& renderer)
    {
    }

    Vector2 MainLevel::GetRandomPositionOnScreen()
    {
        Random rand;

        int randomXPos = rand.GetInt(-500, 500);
        int randomYPos = rand.GetInt(-500, 500);
        return Vector2(randomXPos, randomYPos);
    }
}
