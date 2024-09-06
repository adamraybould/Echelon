#include "States/Level.h"
#include "Systems/EntityManager.h"
#include "Core/Utility.h"

namespace Core::States
{
    Level::Level(EntityManager& entityManager) : m_entityManager(entityManager)
    {
    }

    Level::~Level()
    {
    }

    void Level::Initialize()
    {
    }
}
