#include "Entities/BlankCharacter.h"
#include "Graphics/AssetManager.h"
#include "ECS/Components/SpriteRenderer.h"
#include "Utility/Utility.h"

namespace Echelon::Entities
{
    BlankCharacter::BlankCharacter()
    {
        Engine::Graphics::SpriteSheet& spriteSheet = Engine::Graphics::AssetManager::LoadSpriteSheet("Characters/SS_HumanBase");
        m_renderer = &AddComponent<SpriteRenderer>(*this, spriteSheet);

        Engine::Random rand;
        m_renderer->SetSpriteFrame(rand.Choose(0, 4));
    }

    void BlankCharacter::Initialize()
    {
        Transform().Scale = Vector2(4.0f, 4.0f);
    }

    void BlankCharacter::Update(float delta)
    {
        Entity::Update(delta);
    }

    void BlankCharacter::Render(Renderer& renderer)
    {
        Entity::Render(renderer);
    }
}
