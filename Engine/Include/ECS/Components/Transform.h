#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Component.h"

namespace Engine::ECS
{
    class Transform : public Component
    {
    public:
        Vector2 Position;   // Local Position
        float Rotation;     // Local Rotation
        Vector2 Scale;      // Local Scale

    private:
        Transform* m_parent;
        Array<Transform*> m_children;

    public:
        Transform(Entity& owner);

        void Update(float delta) override;

        void SetParent(Transform& parent);
        void RemoveParent();

        void AddChild(Transform& child);
        void RemoveChild(Transform& child);

        bool HasParent() const { return m_parent != nullptr; }
        Array<Transform*>& GetChildren() { return m_children; }

        void SetWorldPosition(const Vector2& position);
        void AddWorldPosition(const Vector2& position);
        Vector2 GetWorldPosition() const;

        void SetWorldRotation(float rotation);
        float GetWorldRotation() const;

        void SetWorldScale(const Vector2& scale);
        Vector2 GetWorldScale() const;

    private:
        Vector2 Rotate(const Vector2& point, float angle) const;
    };
}

#endif //TRANSFORM_H
