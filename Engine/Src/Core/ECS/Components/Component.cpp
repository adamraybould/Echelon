#include "Engine/Core/ECS/Components/Component.h"

#include "Engine/Utility/Utility.h"

namespace Core::Components
{
    Component::Component(Entity& owner) : m_rOwner(owner)
    {
        m_ID = Utility::GenerateUniqueID();
        SetActive(true);
    }
}
