#include "Engine/Core/Scripting/ScriptComponent.h"

namespace Core::Scripting
{
    ScriptComponent::ScriptComponent(Entity& owner): Component(owner)
    {
    }

    ScriptComponent::~ScriptComponent()
    {
    }

    void ScriptComponent::Initialize()
    {
        Component::Initialize();
    }

    void ScriptComponent::Update(float delta)
    {
        Component::Update(delta);
    }

    void ScriptComponent::Render(Renderer& renderer)
    {
        Component::Render(renderer);
    }

    void ScriptComponent::Destroy()
    {
        Component::Destroy();
    }
}
