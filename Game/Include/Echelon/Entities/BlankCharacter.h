#ifndef BLANKCHARACTER_H
#define BLANKCHARACTER_H
#include "Engine/Core/ECS/Entity.h"

namespace Core::Components
{
    class SpriteRenderer;
}

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
