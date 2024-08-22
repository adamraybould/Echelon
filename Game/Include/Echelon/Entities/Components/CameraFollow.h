#ifndef CAMERAFOLLOW_H
#define CAMERAFOLLOW_H
#include "Engine/Core/ECS/Components/Component.h"

using namespace Core;
namespace Echelon::Entities::Components
{
    class CameraFollow final : public Component
    {
    private:
        Entity& m_target;

        float m_followSpeed;
        float m_followRange;
        bool m_canFollow;

        float m_smoothing;
        bool m_isFollowing;

    public:
        CameraFollow(Entity& owner, Entity& target);

        void Initialize() override;
        void Update(float delta) override;

    private:
        bool IsTargetOutOfRange() const;
        Vector2 GetDirectionToTarget() const;
    };
}

#endif //CAMERAFOLLOW_H
