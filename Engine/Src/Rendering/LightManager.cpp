#include "Rendering/LightManager.h"

namespace Rendering
{
    Array<UniquePtr<Light>> LightManager::m_pLights;

    LightManager::LightManager()
    {
    }

    LightManager::~LightManager()
    {
        for (auto& light : m_pLights)
        {
            light.reset();
        }

        m_pLights.clear();
    }

    Light& LightManager::CreateLight(Vector2F position, Color color, float intensity, float radius)
    {
        m_pLights.push_back(std::make_unique<Light>(position, color, intensity, radius));
        return *m_pLights.back();
    }
}
