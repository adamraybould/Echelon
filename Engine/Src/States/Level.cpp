#include "States/Level.h"
#include "Systems/EntityManager.h"
#include "Utility/Utility.h"

namespace Engine::States
{
    Level::Level()
    {
        m_ID = Utility::GenerateUniqueID();
        m_pEntityManager = std::make_unique<Systems::EntityManager>();
    }

    Level::~Level()
    {
        m_pEntityManager.reset();
    }

    void Level::Initialize()
    {
        if (m_pEntityManager != nullptr)
        {
            m_pEntityManager->InitializeEntities();
        }
    }

    void Level::Update(float delta)
    {
        if (m_pEntityManager != nullptr)
        {
            m_pEntityManager->UpdateEntities(delta);
        }
    }

    void Level::Render(SDL_Renderer& renderer)
    {
        if (m_pEntityManager != nullptr)
        {
            m_pEntityManager->RenderEntities(renderer);
        }
    }
}
