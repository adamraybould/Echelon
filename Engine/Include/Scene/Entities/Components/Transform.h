#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "Core/Maths/Vector2.h"

namespace Core::Components
{
    class Transform : public Component
    {
    public:
        Vector2F Position;   // Local Position
        float Rotation;     // Local Rotation
        Vector2F Scale;      // Local Scale

    private:
        Transform* m_parent;
        Array<Transform*> m_children;

    public:
        Transform(Entity& owner);

        void Update(float delta) override;

        void SetParent(Transform* parent);
        void RemoveParent();

        void AddChild(Transform& child);
        void RemoveChild(Transform& child);

        bool HasParent() const { return m_parent != nullptr; }
        Array<Transform*>& GetChildren() { return m_children; }

        void SetWorldPosition(const Vector2F& position);
        void SetWorldPositionL(LRef position);
        void AddWorldPosition(const Vector2F& position);
        void AddWorldPositionL(LRef position);
        Vector2F GetWorldPosition() const;


        void SetWorldRotation(float rotation);
        float GetWorldRotation() const;

        void SetWorldScale(const Vector2F& scale);
        void SetWorldScaleRaw(float x, float y);
        Vector2F GetWorldScale() const;

        void SetupEmbedding(lua_State* L) override;
    private:
        Vector2F Rotate(const Vector2F& point, float angle) const;
    };
}

#endif //TRANSFORM_H
