#include "Entities/Components/PlayerController.h"

#include <iostream>

#include "ECS/Entity.h"
#include "Systems/InputManager.h"

using namespace Engine::Systems;
namespace Echelon::Entities::Components
{
    PlayerController::PlayerController(Entity& owner) : Component(owner)
    {
        m_walkSpeed = 250.0f;
        m_sprintSpeed = 400.0f;

        m_pSpriteRenderer = GetOwner().GetComponent<SpriteRenderer>();
    }

    void PlayerController::Initialize()
    {
    }

    void PlayerController::Update(float delta)
    {
        ProcessMovement(delta);
    }

    void PlayerController::Render(SDL_Renderer& renderer)
    {
    }

    void PlayerController::Destroy()
    {
    }

    void PlayerController::ProcessMovement(float delta)
    {
        Vector2 movementDirection = Vector2::Zero();

        if (InputManager::IsKeyDown(Keys::W))
        {
            movementDirection = Vector2(movementDirection.X, -1.0f);
            m_pSpriteRenderer->SetSpriteFrame(1);
        }
        else if (InputManager::IsKeyDown(Keys::S))
        {
            movementDirection = Vector2(movementDirection.X, 1.0f);
            m_pSpriteRenderer->SetSpriteFrame(0);
        }

        if (InputManager::IsKeyDown(Keys::A))
        {
            movementDirection = Vector2(-1.0f ,movementDirection.Y);
            m_pSpriteRenderer->SetSpriteFrame(3);
        }
        else if (InputManager::IsKeyDown(Keys::D))
        {
            movementDirection = Vector2(1.0f ,movementDirection.Y);
            m_pSpriteRenderer->SetSpriteFrame(2);
        }

        // Sprint
        if (InputManager::IsKeyDown(Keys::SHIFT))
        {
            m_isSprinting = true;
        }
        else
        {
            m_isSprinting = false;
        }

        GetOwner().Transform().Position += movementDirection.Normalize() * (GetMovementSpeed() * delta);
    }

    float PlayerController::GetMovementSpeed() const
    {
        return m_isSprinting ? m_sprintSpeed : m_walkSpeed;
    }
}
