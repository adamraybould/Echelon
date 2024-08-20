#include "Rendering/Camera.h"

#include "Systems/InputManager.h"
#include "Utility/Constants.h"

using namespace Engine::Systems;
namespace Engine::Rendering
{
    Camera::Camera()
    {
        m_viewport = Rectangle(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
        m_speed = 300.0f;
    }

    void Camera::Update(float delta)
    {
        Vector2 movementDirection = Vector2::Zero();

        if (InputManager::IsKeyDown(Keys::UP))
        {
            movementDirection = Vector2(movementDirection.X, -1.0f);
        }
        else if (InputManager::IsKeyDown(Keys::DOWN))
        {
            movementDirection = Vector2(movementDirection.X, 1.0f);
        }

        if (InputManager::IsKeyDown(Keys::LEFT))
        {
            movementDirection = Vector2(-1.0f, movementDirection.Y);
        }
        else if (InputManager::IsKeyDown(Keys::RIGHT))
        {
            movementDirection = Vector2(1.0f, movementDirection.Y);
        }

        Transform().Position += movementDirection.Normalize() * (m_speed * delta);
    }
}
