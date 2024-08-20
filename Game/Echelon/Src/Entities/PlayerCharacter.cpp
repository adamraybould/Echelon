#include "Entities/PlayerCharacter.h"
#include "ECS/Components/SpriteRenderer.h"
#include "Graphics/AssetManager.h"
#include "Graphics/Sprite.h"
#include "Entities/Components/PlayerController.h"

namespace Echelon::Entities
{
    PlayerCharacter::PlayerCharacter()
    {
        SpriteSheet& spriteSheet = AssetManager::LoadSpriteSheet("Characters/SS_HumanBase");
        m_renderer = &AddComponent<SpriteRenderer>(*this, spriteSheet);

        m_playerController = &AddComponent<PlayerController>(*this);
    }

    void PlayerCharacter::Initialize()
    {
        Transform().Scale = Vector2(4.0f, 4.0f);
    }

    void PlayerCharacter::Update(float delta)
    {
        Entity::Update(delta);
    }

    void PlayerCharacter::Render(Renderer& renderer)
    {
        Entity::Render(renderer);
    }
}
