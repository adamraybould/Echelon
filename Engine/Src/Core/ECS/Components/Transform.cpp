#include "Engine/Core/ECS/Components/Transform.h"

namespace Core::Components
{
    Transform::Transform(Entity& owner) : Component(owner)
    {
        m_parent = nullptr;

        Position = Vector2::Zero();
        Rotation = 0.0f;
        Scale = Vector2::One();
    }

    void Transform::Update(float delta)
    {
    }

    void Transform::SetParent(Transform* parent)
    {
        RemoveParent();
        m_parent = parent;
    }

    void Transform::RemoveParent()
    {
        if (HasParent())
        {
            m_parent->RemoveChild(*this);
            m_parent = nullptr;
        }
    }

    void Transform::AddChild(Transform& child)
    {
        m_children.push_back(&child);
        child.SetParent(this);
    }

    void Transform::RemoveChild(Transform& child)
    {
        for (auto i = m_children.begin(); i != m_children.end(); ++i)
        {
            if (*i == &child)
            {
                m_children.erase(i);
                child.RemoveParent();
            }
        }
    }

    void Transform::SetWorldPosition(const Vector2& position)
    {
        if (HasParent())
        {
            Vector2 worldPosition = position - m_parent->GetWorldPosition();
            worldPosition = Rotate(worldPosition, -m_parent->GetWorldRotation());
            Position = worldPosition / m_parent->GetWorldScale();
        }
        else
        {
            Position = position;
        }
    }

    void Transform::SetWorldPositionL(LRef position)
    {
        SetWorldPosition(Vector2(position["x"], position["y"]));
    }

    void Transform::AddWorldPosition(const Vector2& position)
    {
        Vector2 newPosition = GetWorldPosition() + position;
        SetWorldPosition(newPosition);
    }

    void Transform::AddWorldPositionL(LRef position)
    {
        AddWorldPosition(Vector2(position["x"], position["y"]));
    }

    Vector2 Transform::GetWorldPosition() const
    {
        if (HasParent())
        {
            Vector2 worldPosition = Position;
            worldPosition = worldPosition * m_parent->GetWorldScale();
            worldPosition = Rotate(worldPosition, m_parent->GetWorldRotation());
            worldPosition = worldPosition + m_parent->GetWorldPosition();

            return worldPosition;
        }
        else
        {
            return Position;
        }
    }

    void Transform::SetWorldRotation(float rotation)
    {
        if (HasParent())
        {
            Rotation = rotation - m_parent->GetWorldRotation();
        }
        else
        {
            Rotation = rotation;
        }
    }

    float Transform::GetWorldRotation() const
    {
        if (HasParent())
        {
            return m_parent->GetWorldRotation() + Rotation;
        }
        else
        {
            return Rotation;
        }
    }

    void Transform::SetWorldScale(const Vector2& scale)
    {
        if (HasParent())
        {
            Scale = scale / m_parent->GetWorldScale();
        }
        else
        {
            Scale = scale;
        }
    }

    void Transform::SetWorldScaleRaw(float x, float y)
    {
        SetWorldScale(Vector2(x, y));
    }

    Vector2 Transform::GetWorldScale() const
    {
        if (HasParent())
        {
            return m_parent->GetWorldScale() * Scale;
        }
        else
        {
            return Scale;
        }
    }

    void Transform::SetupEmbedding(lua_State* L)
    {
        Component::SetupEmbedding(L);

        BindClass<Transform>(L);
        BindFunction<Transform>(L, "SetPosition", &Transform::SetWorldPositionL);
        BindFunction<Transform>(L, "AddPosition", &Transform::AddWorldPositionL);
        BindFunction<Transform>(L, "GetWorldPosition", &Transform::GetWorldPosition);

        BindFunction<Transform>(L, "SetRotation", &Transform::SetWorldRotation);
        BindFunction<Transform>(L, "GetRotation", &Transform::GetWorldRotation);

        BindFunction<Transform>(L, "SetScale", &Transform::SetWorldScaleRaw);
        BindFunction<Transform>(L, "GetScale", &Transform::GetWorldScale);

        BindFunction<Transform>(L, "SetParent", &Transform::SetParent);
    }

    Vector2 Transform::Rotate(const Vector2& point, float angle) const
    {
        float rad = angle * (M_PI / 180.0f);
        float cosTheta = cos(rad);
        float sinTheta = sin(rad);

        return Vector2(point.X * cosTheta - point.Y * sinTheta, point.X * sinTheta + point.Y * cosTheta);
    }
}
