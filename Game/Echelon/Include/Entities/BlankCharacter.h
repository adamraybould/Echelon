#ifndef BLANKCHARACTER_H
#define BLANKCHARACTER_H
#include "ECS/Entity.h"

namespace Engine::ECS
{
    class SpriteRenderer;
}

using namespace Engine::ECS;
namespace Echelon::Entities
{
    class BlankCharacter : public Entity
    {
    private:
        SpriteRenderer* m_renderer;

        float m_orbitSpeed;
        float m_orbitRadius;

    public:
        BlankCharacter();

        void Initialize() override;
        void Update(float delta) override;
        void Render(Renderer& renderer) override;

    private:
        void Orbit(float delta, float speed, float radius) const;
    };
}

#endif //BLANKCHARACTER_H
