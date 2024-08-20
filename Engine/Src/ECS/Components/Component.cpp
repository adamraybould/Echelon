#include "ECS/Components/Component.h"

#include "Utility/Utility.h"

namespace Engine::ECS
{
    Component::Component(Entity& owner) : m_rOwner(owner)
    {
        m_ID = Utility::GenerateUniqueID();
        SetActive(true);
    }
}
