#include "Engine/Rendering/Camera.h"
#include "Engine/Systems/InputManager.h"
#include "Engine/Utility/Constants.h"

using namespace Core::Systems;
namespace Core::Rendering
{
    Camera* Camera::m_instance;

    Camera::Camera()
    {
        m_instance = this;

        m_cameraOrigin = Vector2::Zero();
        m_viewport = CalculateViewport();

        m_movementSpeed = 100.0f;

        m_zoom = 1.0f;
        m_zoomSpeed = 4.0f;
    }

    void Camera::Initialize()
    {
    }

    void Camera::Update(float delta)
    {
        Entity::Update(delta);

        ProcessMovement(delta);
        ProcessZoom(delta);

        m_viewport = CalculateViewport();
    }

    void Camera::Render(Renderer& renderer)
    {
        Entity::Render(renderer);
    }

    Vector2 Camera::CalculateScreenPosition(const Vector2& worldPosition) const
    {
        Vector2 screenPosition = worldPosition - m_cameraOrigin;
        return Vector2(screenPosition.X + (SCREEN_WIDTH * 0.5f), screenPosition.Y + (SCREEN_HEIGHT * 0.5f));
    }

    Vector2 Camera::CalculateWorldPosition(const Vector2& screenPosition) const
    {
        return screenPosition + m_cameraOrigin;
    }

    void Camera::ProcessMovement(float delta) const
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

        GetTransform().Position += movementDirection.Normalize() * (m_movementSpeed * delta);
    }

    void Camera::ProcessZoom(float delta)
    {
        m_zoom += InputManager::GetMouseWheel() * (m_zoomSpeed * delta);

        float zoomX = SCREEN_WIDTH / m_zoom;
        float zoomY = SCREEN_HEIGHT / m_zoom;
        Vector2 newPosition = GetTransform().GetWorldPosition() + Vector2((SCREEN_WIDTH - zoomX) * 0.5f, (SCREEN_HEIGHT  - zoomY) * 0.5f);
        m_cameraOrigin = newPosition;
    }

    Rectangle Camera::CalculateViewport() const
    {
        return Rectangle(0.0f, 0.0f, SCREEN_WIDTH / m_zoom, SCREEN_HEIGHT / m_zoom);
    }
}
