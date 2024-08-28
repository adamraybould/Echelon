#include "Echelon/Levels/MainLevel.h"

#include "Echelon/Entities/PlayerCharacter.h"
#include "Echelon/Entities/Components/CameraFollow.h"
#include <Engine/Core/Camera.h>
#include <Engine/Utility/Utility.h>

#include "Engine/Core/God.h"

using namespace Core;
namespace Echelon::Levels
{
    MainLevel::MainLevel(EntityManager& entityManager) : Level(entityManager)
    {
        //Vector2 centerPosition = Vector2((SCREEN_WIDTH / 2) - 32, (SCREEN_HEIGHT / 2) - 32);
        /*
        m_pPlayer = &Instantiate<PlayerCharacter>("Player");

        Entity* camera = Camera::Main;
        if (camera != nullptr)
            camera->AddComponent<CameraFollow>(*m_pPlayer);
            */
    }

    MainLevel::~MainLevel()
    {
    }

    void MainLevel::Initialize()
    {
        //Level::Initialize();
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
