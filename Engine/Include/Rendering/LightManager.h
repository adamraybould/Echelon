#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H
#include "Core/TypeDefs.h"
#include "Core/Commons.h"
#include "Core/System.h"
#include "Core/Maths/Vector2.h"

namespace Rendering
{
    struct Light
    {
        Vector2F Position;
        Color LightColor;
        float Intensity = 1.0f;
        float Radius = 1.0f;

        Light(const Vector2F& position, const Color& color, const float intensity, const float radius)
        {
            Position = position;
            LightColor = color;
            Intensity = intensity;
            Radius = radius;
        }
    };

    class LightManager final : System
    {
    private:
        static Array<UniquePtr<Light>> m_pLights;

    public:
        LightManager();
        ~LightManager() override;

        static Light& CreateLight(Vector2F position, Color color, float intensity, float radius);
        Array<UniquePtr<Light>>& GetLights() const { return m_pLights; }
    };
}


#endif //LIGHTMANAGER_H
