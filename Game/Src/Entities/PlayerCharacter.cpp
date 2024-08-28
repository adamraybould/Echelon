#include "Echelon/Entities/PlayerCharacter.h"
#include "Engine/Core/ECS/Components/SpriteRenderer.h"
#include "Engine/Graphics/AssetManager.h"
#include "Echelon/Entities/Components/PlayerController.h"
#include "Engine/Core/Camera.h"

namespace Echelon::Entities
{
    PlayerCharacter::PlayerCharacter(const char* name) : Entity(name)
    {
        AddTransform();

        SpriteSheet& spriteSheet = AssetManager::LoadSpriteSheet("Characters/SS_HumanBase");
        m_renderer = &AddComponent<SpriteRenderer>();

        m_playerController = &AddComponent<PlayerController>();
    }

    void PlayerCharacter::Initialize()
    {
        Entity::Initialize();

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
