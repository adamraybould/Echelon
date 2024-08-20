#ifndef CAMERA_H
#define CAMERA_H
#include "Utility/Commons.h"

namespace Engine::Rendering
{
    class Camera
    {
    private:
        Transform m_transform;
        Rectangle m_viewport;

        float m_speed;

    public:
        Camera();
        
        void Update(float delta);

        Transform& Transform() { return m_transform; }
        Rectangle& GetViewport() { return m_viewport; }
    };
}

#endif //CAMERA_H
