#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include "Component.h"
#include "Core/Commons.h"

namespace Rendering
{
    struct Light;
}

namespace Scene
{
    namespace Components
    {
        class LightSource final : public Component
        {
        private:
            Rendering::Light* m_pLight = nullptr;

            Color m_lightColor = Color(255, 255, 255);
            float m_lightIntensity = 1.0f;
            float m_lightRadius = 1.0f;

        public:
            LightSource(Entity& owner);

            void SetupEmbedding(lua_State* L) override;
            void Initialize() override;
            void Update(float delta) override;
            void Destroy() override;

            void SetColor(const int r, const int g, const int b) { m_lightColor = Color(r, g, b); }
            void SetIntensity(const float value) { m_lightIntensity = value; }
            void SetRadius(const float value) { m_lightRadius = value; }
        };
    }
}

#endif //LIGHTSOURCE_H
