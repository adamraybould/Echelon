#include "Echelon/Entities/Mobs/Gunbot.h"

#include <Engine/Graphics/AssetManager.h>
#include <Engine/Graphics/SpriteSheet.h>
#include <Engine/Core/ECS/Components/SpriteRenderer.h>

using namespace Core::Graphics;
namespace Echelon
{
    namespace Entities::Mobs
    {
        Gunbot::Gunbot(const char* name) : Entity(name)
        {
            SpriteSheet& spriteSheet = AssetManager::LoadSpriteSheet("Mobs/Robots/Gunbot");
            m_renderer = &AddComponent<SpriteRenderer>(spriteSheet);
            m_renderer->SetSpriteFrame(36);
        }

        void Gunbot::Initialize()
        {
            GetTransform().SetWorldScale(Vector2(3.0f, 3.0f));
        }

        void Gunbot::Update(float delta)
        {
            Entity::Update(delta);
        }

        void Gunbot::Render(Renderer& renderer)
        {
            Entity::Render(renderer);
        }
    }
}
