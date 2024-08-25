#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H
#include "Engine/Core/ECS/Components/Component.h"

namespace Core::Scripting
{
    class ScriptComponent : public Component
    {
    public:
        ScriptComponent(Entity& owner);
        ~ScriptComponent() override;

        void Initialize() override;
        void Update(float delta) override;
        void Render(Renderer& renderer) override;
        void Destroy() override;
    };
}

#endif //SCRIPTCOMPONENT_H
