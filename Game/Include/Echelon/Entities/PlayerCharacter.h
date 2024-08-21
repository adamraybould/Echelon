#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H
#include "Engine/Core/ECS/Entity.h"

namespace Core::Components
{
    class SpriteRenderer;
}

namespace Echelon::Entities::Components
{
    class PlayerController;
}

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
        void Render(Renderer& renderer) override;
    };
}

#endif //PLAYERCHARACTER_H
