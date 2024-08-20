#include "Levels/MainLevel.h"
#include "Entities/PlayerCharacter.h"

namespace Echelon::Levels
{
    MainLevel::MainLevel()
    {
        m_pPlayer = &CreateEntity<Entities::PlayerCharacter>();
    }

    void MainLevel::Initialize()
    {
        Level::Initialize();
    }

    void MainLevel::Update(float delta)
    {
        Level::Update(delta);
    }

    void MainLevel::Render(SDL_Renderer& renderer)
    {
        Level::Render(renderer);
    }
}
