#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

#include "Scene/Entities/Entity.h"
#include "Commons.h"

namespace Core
{
    class Camera : public Scene::Entity
    {
    public:
        static Camera* Main;

    private:
        glm::mat4 m_projection;
        glm::mat4 m_view;

        Vector2F m_cameraPosition;

        RectF m_viewport;

        float m_movementSpeed;

        float m_currentZoom = 1.0f;
        float m_zoomSpeed;
        MinMaxRangeF m_zoomRange;

        bool m_canControl = false;

    public:
        Camera(const char* name);
        void SetupEmbedding(lua_State* L) override;

        void Initialize() override;
        void Update(float delta) override;

        void Zoom(float amount);

        Vector2F CalculateScreenPosition(const Vector2F& worldPosition) const;
        Vector2F CalculateWorldPosition(Vector2F screenPosition) const;

        Vector2F& GetCameraPosition() { return m_cameraPosition; }
        RectF& GetViewport() { return m_viewport; }
        float GetZoom() const { return m_currentZoom; }

        glm::mat4& GetProjection() { return m_projection; }
        glm::mat4& GetView() { return m_view; }

    private:
        void UpdateProjection();
        void UpdateView();

        void ProcessZoom(float delta);
        RectF CalculateViewport() const;
    };
}

#endif //CAMERA_H
