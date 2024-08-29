#ifndef CAMERA_H
#define CAMERA_H
#include "ECS/Entity.h"
#include "Engine/Utility/Commons.h"
#include "Engine/Utility/Constants.h"

namespace Core
{
    class Camera : public Entity
    {
    public:
        static Camera* Main;

    private:
        Vector2 m_cameraOrigin;
        Vector2 m_cameraPosition;

        Rectangle m_viewport;

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

        Vector2 CalculateScreenPosition(const Vector2& worldPosition) const;
        Vector2 CalculateWorldPosition(Vector2 screenPosition) const;

        Vector2& GetPosition() { return m_cameraOrigin; }
        Rectangle& GetViewport() { return m_viewport; }
        float GetZoom() const { return m_currentZoom; }

    private:
        void ProcessMovement(float delta) const;
        void ProcessZoom(float delta);

        Rectangle CalculateViewport() const;
    };
}

#endif //CAMERA_H