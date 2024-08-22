#include "Engine/States/Level.h"
#include "Engine/Core/Systems/EntityManager.h"
#include "Engine/Utility/Utility.h"

namespace Core::States
{
    Level::Level(EntityManager& entityManager) : m_entityManager(entityManager)
    {
        m_ID = Utility::GenerateUniqueID();
    }

    Level::~Level()
    {
    }
}
