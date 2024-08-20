#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H
#include "ECS/Entity.h"

namespace Echelon::Entities::Components
{
    class PlayerController;
}

namespace Engine::ECS
{
    class SpriteRenderer;
}

using namespace Engine::ECS;
using namespace Echelon::Entities::Components;
namespace Echelon::Entities
{
    class PlayerCharacter : public Entity
    {
    private:
        SpriteRenderer* m_renderer;
        PlayerController* m_playerController;

    public:
        PlayerCharacter();

        void Initialize() override;
        void Update(float delta) override;
        void Render(SDL_Renderer& renderer) override;
    };
}

#endif //PLAYERCHARACTER_H
