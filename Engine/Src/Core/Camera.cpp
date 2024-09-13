#include "Core/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

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

        m_cameraPosition = Vector2F::Zero();
        m_viewport = CalculateViewport();

        m_movementSpeed = 100.0f;

        m_currentZoom = 1.0f;
        m_zoomSpeed = 4.0f;
        m_zoomRange = MinMaxRangeF(0.5f, 1.5f);
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

        UpdateProjection();
        UpdateView();
    }

    void Camera::Zoom(const float amount)
    {
        m_currentZoom += amount;
    }

    Vector2F Camera::CalculateScreenPosition(const Vector2F& worldPosition) const
    {
        const glm::vec4 clipCoords = m_projection * m_view * glm::vec4(worldPosition.X, worldPosition.Y, 0.0f, 1.0f);
        const glm::vec3 ndsCoords = glm::vec3(clipCoords) / clipCoords.w;

        float screenX = ((ndsCoords.x + 1.0f) / 2.0f) * SCREEN_WIDTH;
        float screenY = ((1.0f - ndsCoords.y) / 2.0f) * SCREEN_HEIGHT;

        return { screenX, screenY };
    }

    Vector2F Camera::CalculateWorldPosition(const Vector2F screenPosition) const
    {
        float ndcX = (2.0f * screenPosition.X) / SCREEN_WIDTH - 1.0f;
        float ndcY = 1.0f - (2.0f * screenPosition.Y) / SCREEN_HEIGHT;

        const glm::mat4 invProjView = glm::inverse(m_projection * m_view);
        glm::vec4 worldPos = invProjView * glm::vec4(ndcX, ndcY, 0.0f, 1.0f);

        return { worldPos.x, worldPos.y };
    }

    void Camera::UpdateProjection()
    {
        constexpr float halfWidth = SCREEN_WIDTH * 0.5f;
        constexpr float halfHeight = SCREEN_HEIGHT * 0.5f;

        float zoomedWidth = halfWidth / m_currentZoom;
        float zoomedHeight = halfHeight / m_currentZoom;

        m_projection = glm::ortho(-zoomedWidth, zoomedWidth, -zoomedHeight, zoomedHeight, -1.0f, 100.0f);
    }

    void Camera::UpdateView()
    {
        m_view = translate(glm::mat4(1.0f), glm::vec3(-m_cameraPosition.X, -m_cameraPosition.Y, 0.0f));
        m_view = rotate(m_view, glm::radians(0.0f), glm::vec3(0, 0, 1));
    }

    void Camera::ProcessZoom(const float delta)
    {
        m_currentZoom += Input::GetMouseWheel() * (m_zoomSpeed * delta);
        m_currentZoom = MathF::Clamp(GetZoom(), m_zoomRange.Min, m_zoomRange.Max);

        m_cameraPosition = GetTransform().GetWorldPosition();
    }

    RectF Camera::CalculateViewport() const
    {
        return { m_cameraPosition.X, m_cameraPosition.Y, SCREEN_WIDTH / m_currentZoom, SCREEN_HEIGHT / m_currentZoom };
    }
}
