#include "Entities/Components/CameraFollow.h"

#include <cmath>
#include <iostream>

#include "ECS/Entity.h"
#include "ECS/Components/Transform.h"
#include "Utility/MathF.h"

using namespace Engine;
namespace Echelon::Entities::Components
{
    CameraFollow::CameraFollow(Entity& owner, Entity& target) : Component(owner), m_target(target)
    {
        m_followSpeed = 50.0f;
        m_followRange = 30.0f;
        m_canFollow = true;

        m_smoothing = 4.0f;
        m_isFollowing = false;
    }

    void CameraFollow::Initialize()
    {
    }

    void CameraFollow::Update(float delta)
    {
        if (m_canFollow)
        {
            if (IsTargetOutOfRange())
            {
                m_isFollowing = true;
            }

            if (m_isFollowing)
            {
                const Vector2& position = GetOwner().GetTransform().Position;
                const Vector2& targetPosition = m_target.GetTransform().Position;
                const float distance = (targetPosition - position).Length();

                // Set Position to Target if Close Enough
                if (distance < m_followSpeed * delta)
                {
                    GetOwner().GetTransform().Position = targetPosition;
                    m_isFollowing = false;
                }
                else
                {
                    GetOwner().GetTransform().Position = MathF::Lerp(position, targetPosition, m_smoothing * delta);
                }
            }
        }
    }

    bool CameraFollow::IsTargetOutOfRange() const
    {
        return GetDirectionToTarget().Length() > m_followRange;
    }

    Vector2 CameraFollow::GetDirectionToTarget() const
    {
        const Vector2& position = GetOwner().GetTransform().Position;
        const Vector2& targetPosition = m_target.GetTransform().Position;
        return targetPosition - position;
    }
}
