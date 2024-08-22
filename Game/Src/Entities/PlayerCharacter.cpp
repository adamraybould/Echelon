#include "Echelon/Entities/PlayerCharacter.h"
#include "Engine/Core/ECS/Components/SpriteRenderer.h"
#include "Engine/Graphics/AssetManager.h"
#include "Echelon/Entities/Components/PlayerController.h"
#include "../../../Engine/Include/Engine/Core/Camera.h"

namespace Echelon::Entities
{
    PlayerCharacter::PlayerCharacter(const char* name) : Entity(name)
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
