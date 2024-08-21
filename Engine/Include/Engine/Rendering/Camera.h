#ifndef CAMERA_H
#define CAMERA_H
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Utility/Commons.h"

namespace Core::Rendering
{
    class Camera : public Entity
    {
    private:
        static Camera* m_instance;

        Vector2 m_cameraOrigin;
        Vector2 m_cameraPosition;

        Rectangle m_viewport;

        float m_movementSpeed;

        float m_zoom = 1.0f;
        float m_zoomSpeed;

    public:
        Camera();

        void Initialize() override;
        void Update(float delta) override;
        void Render(Renderer& renderer) override;

        Vector2 CalculateScreenPosition(const Vector2& worldPosition) const;
        Vector2 CalculateWorldPosition(const Vector2& screenPosition) const;

        Vector2& GetPosition() { return m_cameraOrigin; }
        Rectangle& GetViewport() { return m_viewport; }
        float GetZoom() { return m_zoom; }

        static Camera* Main() { return m_instance; }

    private:
        void ProcessMovement(float delta) const;
        void ProcessZoom(float delta);

        Rectangle CalculateViewport() const;
    };
}

#endif //CAMERA_H
