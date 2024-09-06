#include "Core/Camera.h"

#include "Core/IO/Input.h"
#include "Core/Constants.h"
#include "Core//Maths/MathF.h"

namespace Core
{
    Camera* Camera::Main;

    Camera::Camera(const char* name) : Entity(name)
    {
        Main = this;

        AddTransform(nullptr);

        m_cameraOrigin = Vector2F::Zero();
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

    void Camera::Update(const float delta)
    {
        Entity::Update(delta);

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

    Vector2F Camera::CalculateScreenPosition(const Vector2F& worldPosition) const
    {
        Vector2F screenPosition = worldPosition - m_cameraOrigin;
        return { screenPosition.X + SCREEN_WIDTH * 0.5f, screenPosition.Y + SCREEN_HEIGHT * 0.5f };
    }

    Vector2F Camera::CalculateWorldPosition(const Vector2F screenPosition) const
    {
        Vector2F worldPosition = screenPosition / GetZoom() + m_cameraOrigin;
        return { worldPosition.X - SCREEN_WIDTH * 0.5f, worldPosition.Y - SCREEN_HEIGHT * 0.5f };
    }

    void Camera::ProcessZoom(const float delta)
    {
        m_currentZoom += Input::GetMouseWheel() * (m_zoomSpeed * delta);
        m_currentZoom = MathF::Clamp(GetZoom(), m_zoomRange.Min, m_zoomRange.Max);

        float zoomX = SCREEN_WIDTH / GetZoom();
        float zoomY = SCREEN_HEIGHT / GetZoom();
        m_cameraOrigin = GetTransform().GetWorldPosition() + Vector2((SCREEN_WIDTH - zoomX) * 0.5f, (SCREEN_HEIGHT  - zoomY) * 0.5f);
    }

    RectI Camera::CalculateViewport() const
    {
        return { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    }
}
