#include "Entities/PlayerCharacter.h"
#include "ECS/Components/SpriteRenderer.h"
#include "Graphics/AssetManager.h"
#include "Graphics/Sprite.h"
#include "Entities/Components/PlayerController.h"
#include "Rendering/Camera.h"

namespace Echelon::Entities
{
    PlayerCharacter::PlayerCharacter()
    {
        SpriteSheet& spriteSheet = AssetManager::LoadSpriteSheet("Characters/SS_HumanBase");
        m_renderer = &AddComponent<SpriteRenderer>(spriteSheet);

        m_playerController = &AddComponent<PlayerController>();

    }

    void PlayerCharacter::Initialize()
    {
        GetTransform().Scale = Vector2(3.0f, 3.0f);

        //GetTransform().AddChild(Camera::Main()->GetTransform());
        //Camera::Main()->GetTransform().SetParent(GetTransform());
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
