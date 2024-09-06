#include "Scene/Entities/Components/Transform.h"

namespace Scene
{
    namespace Components
    {
        Transform::Transform(Entity& owner) : Component(owner)
        {
            m_parent = nullptr;

            Position = Vector2F::Zero();
            Rotation = 0.0f;
            Scale = Vector2F::One();
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

        void Transform::SetWorldPosition(const Vector2F& position)
        {
            if (HasParent())
            {
                Vector2F worldPosition = position - m_parent->GetWorldPosition();
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
            SetWorldPosition(Vector2F(position["x"], position["y"]));
        }

        void Transform::AddWorldPosition(const Vector2F& position)
        {
            Vector2F newPosition = GetWorldPosition() + position;
            SetWorldPosition(newPosition);
        }

        void Transform::AddWorldPositionL(LRef position)
        {
            AddWorldPosition(Vector2F(position["x"], position["y"]));
        }

        Vector2F Transform::GetWorldPosition() const
        {
            if (HasParent())
            {
                Vector2F worldPosition = Position;
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

        void Transform::SetWorldRotation(const float rotation)
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

        void Transform::SetWorldScale(const Vector2F& scale)
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
            SetWorldScale(Vector2F(x, y));
        }

        Vector2F Transform::GetWorldScale() const
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

        Vector2F Transform::Rotate(const Vector2F& point, const float angle) const
        {
            const float rad = angle * (M_PI / 180.0f);
            const float cosTheta = cos(rad);
            const float sinTheta = sin(rad);

            return Vector2F(point.X * cosTheta - point.Y * sinTheta, point.X * sinTheta + point.Y * cosTheta);
        }
    }
}
