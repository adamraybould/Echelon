#include "Echelon/Entities/BlankCharacter.h"

#include <Engine/Graphics/AssetManager.h>
#include <Engine/Core/ECS/Components/SpriteRenderer.h>
#include <Engine/Utility/Utility.h>

namespace Echelon::Entities
{
    BlankCharacter::BlankCharacter(const char* name) : Entity(name)
    {
        SpriteSheet& spriteSheet = AssetManager::LoadSpriteSheet("Characters/SS_HumanBase");
        m_renderer = &AddComponent<SpriteRenderer>(spriteSheet);

        Random rand;
        m_renderer->SetSpriteFrame(rand.Choose(0, 4));

        m_orbitSpeed = rand.GetFloat(10.0f, 60.0f);
        m_orbitRadius = rand.GetFloat(150.0f, 200.0f);
    }

    void BlankCharacter::Initialize()
    {
        GetTransform().SetWorldScale(Vector2(3.0f, 3.0f));
    }

    void BlankCharacter::Update(float delta)
    {
        //Orbit(delta, m_orbitSpeed, m_orbitRadius);
        Entity::Update(delta);
    }

    void BlankCharacter::Render(Renderer& renderer)
    {
        Entity::Render(renderer);
    }

    void BlankCharacter::Orbit(float delta, float speed, float radius) const
    {
        if (GetTransform().HasParent())
        {
            static float angle = 0.0f;
            angle += speed * delta;

            float rad = angle * (M_PI / 180.0f);

            float orbitX = radius * cos(rad);
            float orbitY = radius * sin(rad);

            GetTransform().Position = Vector2(orbitX, orbitY);
            GetTransform().Rotation = angle + 90.0f;
        }
    }
}
