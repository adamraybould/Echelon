#ifndef CAMERA_H
#define CAMERA_H
#include "Utility/Commons.h"

namespace Engine::Rendering
{
    class Camera
    {
    private:
        Vector2 m_cameraOrigin;
        Vector2 m_cameraPosition;

        Rectangle m_viewport;

        float m_movementSpeed;

        float m_zoom = 1.0f;
        float m_zoomSpeed;

    public:
        Camera();

        void Update(float delta);

        Vector2 CalculateScreenPosition(const Vector2& worldPosition) const;
        Vector2 CalculateWorldPosition(const Vector2& screenPosition) const;

        Vector2& GetPosition() { return m_cameraOrigin; }
        Rectangle& GetViewport() { return m_viewport; }
        float GetZoom() { return m_zoom; }

    private:
        void ProcessMovement(float delta);
        void ProcessZoom(float delta);

        Rectangle CalculateViewport() const;
    };
}

#endif //CAMERA_H
