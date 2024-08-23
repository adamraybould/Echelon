#include "Echelon/Entities/Mobs/Drillbot.h"

#include "Engine/Core/ECS/Components/SpriteRenderer.h"
#include "Engine/Graphics/AssetManager.h"

namespace Echelon
{
    namespace Entities::Mobs
    {
        Drillbot::Drillbot(const char* name) : Entity(name)
        {
            Graphics::SpriteSheet& spriteSheet = AssetManager::LoadSpriteSheet("Mobs/Robots/Drillbot");
            m_renderer = &AddComponent<SpriteRenderer>(spriteSheet);
            //m_renderer->SetSpriteFrame(0);
        }

        void Drillbot::Initialize()
        {
            GetTransform().SetWorldScale(Vector2(3.0f, 3.0f));
        }

        void Drillbot::Update(float delta)
        {
            Entity::Update(delta);
        }

        void Drillbot::Render(Renderer& renderer)
        {
            Entity::Render(renderer);
        }
    }
}
