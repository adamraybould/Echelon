#ifndef LEVEL_H
#define LEVEL_H
#include "Utility/Commons.h"

namespace Engine::Systems
{
    class EntityManager;
}

namespace Engine::Rendering
{
    class Renderer;
}

using namespace Engine::Rendering;
namespace Engine::States
{
    class Level
    {
    private:
        UInt64 m_ID;
        UniquePtr<Systems::EntityManager> m_pEntityManager;

    public:
        Level();
        virtual ~Level();

        virtual void Initialize();
        virtual void Update(float delta);
        virtual void Render(Renderer& renderer);

        UInt64 GetID() const { return m_ID; }
        Systems::EntityManager& GetEntityManager() const { return *m_pEntityManager; }
    };
}

#endif //LEVEL_H
