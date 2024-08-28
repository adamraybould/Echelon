#ifndef VECTOR2_H
#define VECTOR2_H
#include <cmath>
#include <string>

using String = std::string;

struct SDL_Point;
namespace Core::Maths
{
    struct Vector2
    {
        float X;
        float Y;

        Vector2()
        {
            X = 0.0f;
            Y = 0.0f;
        }

        Vector2(float x, float y)
        {
            X = x;
            Y = y;
        }

        void Set(float x, float y)
        {
            this->X = x;
            this->Y = y;
        }

        float Length() const { return sqrtf(X * X + Y * Y); }
        float Distance(const Vector2& vec) const { return sqrtf((vec.X - X) * (vec.X - X) + (vec.Y - Y) * (vec.Y - Y)); }
        float Dot(const Vector2& vec) const { return (X * vec.X + Y * vec.Y); }

        Vector2& Normalize()
        {
            float xxyy = X * X + Y * Y;
            if (xxyy == 0) xxyy = 1;

            float invLength = 1.0f / sqrtf(xxyy);
            X *= invLength;
            Y *= invLength;
            return *this;
        }

        Vector2 operator-() const { return Vector2(-X, -Y); }
        Vector2 operator+(const Vector2& rhs) const { return Vector2(X + rhs.X, Y + rhs.Y); }
        Vector2 operator-(const Vector2& rhs) const { return Vector2(X - rhs.X, Y - rhs.Y); }
        Vector2& operator+=(const Vector2& rhs) { X += rhs.X; Y += rhs.Y; return *this; }
        Vector2& operator-=(const Vector2& rhs) { X -= rhs.X; Y -= rhs.Y; return *this; }
        Vector2& operator-=(const float scale) { X -= scale; Y -= scale; return *this; }
        Vector2 operator*(const float scale) const { return Vector2(X * scale, Y * scale); }
        Vector2 operator*(const Vector2& rhs) const { return Vector2(X * rhs.X, Y * rhs.Y); }
        Vector2& operator*=(const float scale) { X *= scale; Y *= scale; return *this; }
        Vector2& operator*=(const Vector2& rhs) { X *= rhs.X; Y *= rhs.Y; return *this; }
        Vector2 operator/(const float scale) const { return Vector2(X / scale, Y / scale); }
        Vector2 operator/(const Vector2& rhs) const { return Vector2(X / rhs.X, Y / rhs.Y); }
        Vector2& operator/=(const float scale) { X /= scale; Y /= scale; return *this; }
        bool operator==(const Vector2& rhs) const { return (X == rhs.X) && (Y == rhs.Y); }
        bool operator!=(const Vector2& rhs) const { return (X != rhs.X) && (Y != rhs.Y); }

        String ToString() const { return "Vector2(" + std::to_string(X) + ", " + std::to_string(Y) + ")"; }

        static Vector2 One() { return Vector2(1.0f, 1.0f); }
        static Vector2 Zero() { return Vector2(0.0f, 0.0f); }

        explicit operator SDL_Point* () const;
    };
}
#endif //VECTOR2_H
