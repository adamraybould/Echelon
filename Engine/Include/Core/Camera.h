#ifndef CAMERA_H
#define CAMERA_H
#include "Scene/Entities/Entity.h"
#include "Commons.h"

namespace Core
{
    class Camera : public Entity
    {
    public:
        static Camera* Main;

    private:
        Vector2F m_cameraOrigin;
        Vector2F m_cameraPosition;

        RectI m_viewport;

        float m_movementSpeed;

        float m_currentZoom = 1.0f;
        float m_zoomSpeed;
        MinMaxRange m_zoomRange;

        bool m_canControl = false;

    public:
        Camera(const char* name);
        void SetupEmbedding(lua_State* L) override;

        void Initialize() override;
        void Update(float delta) override;
        void Render(Renderer& renderer) override;

        void Zoom(float amount);

        Vector2F CalculateScreenPosition(const Vector2F& worldPosition) const;
        Vector2F CalculateWorldPosition(Vector2F screenPosition) const;

        Vector2F& GetCameraOrigin() { return m_cameraOrigin; }
        RectI& GetViewport() { return m_viewport; }
        float GetZoom() const { return m_currentZoom; }

    private:
        void ProcessZoom(float delta);
        RectI CalculateViewport() const;
    };
}

#endif //CAMERA_H
