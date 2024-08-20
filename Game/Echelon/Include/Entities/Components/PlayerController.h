#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "ECS/Components/Component.h"
#include "ECS/Components/SpriteRenderer.h"

using namespace Engine::ECS;
namespace Echelon::Entities::Components
{
    class PlayerController : public Component
    {
    private:
        SpriteRenderer* m_pSpriteRenderer;

        float m_walkSpeed;
        float m_sprintSpeed;
        bool m_isSprinting;

    public:
        PlayerController(Entity& owner);

        void Initialize() override;
        void Update(float delta) override;
        void Render(Renderer& renderer) override;
        void Destroy() override;

    private:
        void ProcessMovement(float delta);
        float GetMovementSpeed() const;
    };
}

#endif //PLAYERCONTROLLER_H
