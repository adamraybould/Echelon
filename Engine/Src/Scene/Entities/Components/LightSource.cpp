#include "Scene/Entities/Components/LightSource.h"

#include "Rendering/LightManager.h"
#include "Scene/Entities/Entity.h"

using namespace Rendering;
namespace Scene
{
    namespace Components
    {
        LightSource::LightSource(Entity& owner) : Component(owner)
        {
        }

        void LightSource::SetupEmbedding(lua_State* L)
        {
            Component::SetupEmbedding(L);

            BindFunction<LightSource>(L, "SetColor", &LightSource::SetColor);
            BindFunction<LightSource>(L, "SetIntensity", &LightSource::SetIntensity);
            BindFunction<LightSource>(L, "SetRadius", &LightSource::SetRadius);
        }

        void LightSource::Initialize()
        {
            m_pLight = &LightManager::CreateLight(GetOwner().GetTransform().GetWorldPosition(), m_lightColor, m_lightIntensity, m_lightRadius);
        }

        void LightSource::Update(const float delta)
        {
            if (m_pLight != nullptr)
            {
                m_pLight->Position = GetOwner().GetTransform().GetWorldPosition();
            }
        }

        void LightSource::Destroy()
        {
        }
    }
}
