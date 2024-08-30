#include "Engine/Core/Camera.h"
#include "Engine/Core/Systems/InputManager.h"
#include "Engine/Utility/Constants.h"
#include "Engine/Utility/MathF.h"

using namespace Core::Systems;
namespace Core
{
    Camera* Camera::Main;

    Camera::Camera(const char* name) : Entity(name)
    {
        Main = this;

        m_transform = &AddComponent<Transform>();

        m_cameraOrigin = Vector2::Zero();
        m_viewport = CalculateViewport();

        m_movementSpeed = 100.0f;

        m_currentZoom = 1.0f;
        m_zoomSpeed = 4.0f;
        m_zoomRange = MinMaxRange(0.5f, 1.5f);
    }

    void Camera::SetupEmbedding(lua_State* L)
    {
        Entity::SetupEmbedding(L);

        BindClass<Camera>(L);
        BindFunction<Camera>(L, "Zoom", &Camera::Zoom);
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

    void Camera::Zoom(const float amount)
    {
        m_currentZoom += amount;
    }

    Vector2 Camera::CalculateScreenPosition(const Vector2& worldPosition) const
    {
        Vector2 screenPosition = worldPosition - m_cameraOrigin;
        return Vector2(screenPosition.X + (SCREEN_WIDTH * 0.5f), screenPosition.Y + (SCREEN_HEIGHT * 0.5f));
    }

    Vector2 Camera::CalculateWorldPosition(const Vector2 screenPosition) const
    {
        Vector2 worldPosition = (screenPosition / GetZoom()) + m_cameraOrigin;
        return Vector2(worldPosition.X - (SCREEN_WIDTH * 0.5f), worldPosition.Y - (SCREEN_HEIGHT * 0.5f));
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
        m_currentZoom += InputManager::GetMouseWheel() * (m_zoomSpeed * delta);
        m_currentZoom = MathF::Clamp(GetZoom(), m_zoomRange.Min, m_zoomRange.Max);

        float zoomX = SCREEN_WIDTH / GetZoom();
        float zoomY = SCREEN_HEIGHT / GetZoom();
        m_cameraOrigin = GetTransform().GetWorldPosition() + Vector2((SCREEN_WIDTH - zoomX) * 0.5f, (SCREEN_HEIGHT  - zoomY) * 0.5f);
    }

    Rectangle Camera::CalculateViewport() const
    {
        return Rectangle(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
}
