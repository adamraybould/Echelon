#ifndef VECTOR2_H
#define VECTOR2_H
#include <cmath>
#include <string>

namespace Core
{
    template <typename T>
    struct Vector2
    {
        T X;
        T Y;

        Vector2() { X = 0; Y = 0; }
        Vector2(T x, T y) { X = x; Y = y; }

        template<typename U = T, typename = std::enable_if_t<!std::is_same_v<U, int>>>
        Vector2(const Vector2<int>& other) { X = static_cast<T>(other.X); Y = static_cast<T>(other.Y); }

        template<typename U = T, typename = std::enable_if_t<!std::is_same_v<U, unsigned>>>
        Vector2(const Vector2<unsigned>& other) { X = static_cast<T>(other.X); Y = static_cast<T>(other.Y); }

        template<typename U = T, typename = std::enable_if_t<!std::is_same_v<U, float>>>
        Vector2(const Vector2<float>& other) { X = static_cast<T>(other.X); Y = static_cast<T>(other.Y); }

        T Length() const { return sqrtf(X * X + Y * Y); }
        T Distance(const Vector2& vec) const { return sqrtf((vec.X - X) * (vec.X - X) + (vec.Y - Y) * (vec.Y - Y)); }
        T Dot(const Vector2& vec) const { return X * vec.X + Y * vec.Y; }

        Vector2& Normalize()
        {
            T xxyy = X * X + Y * Y;
            if (xxyy == 0) xxyy = 1;

            T invLength = 1 / sqrtf(xxyy);
            X *= invLength;
            Y *= invLength;
            return *this;
        }

        Vector2 operator-() const { return Vector2(-X, -Y); }
        Vector2 operator+(const Vector2& rhs) const { return Vector2(X + rhs.X, Y + rhs.Y); }
        Vector2 operator-(const Vector2& rhs) const { return Vector2(X - rhs.X, Y - rhs.Y); }
        Vector2& operator+=(const Vector2& rhs) { X += rhs.X; Y += rhs.Y; return *this; }
        Vector2& operator-=(const Vector2& rhs) { X -= rhs.X; Y -= rhs.Y; return *this; }
        Vector2& operator-=(const T scale) { X -= scale; Y -= scale; return *this; }
        Vector2 operator*(const T scale) const { return Vector2(X * scale, Y * scale); }
        Vector2 operator*(const Vector2& rhs) const { return Vector2(X * rhs.X, Y * rhs.Y); }
        Vector2& operator*=(const T scale) { X *= scale; Y *= scale; return *this; }
        Vector2& operator*=(const Vector2& rhs) { X *= rhs.X; Y *= rhs.Y; return *this; }
        Vector2 operator/(const T scale) const { return Vector2(X / scale, Y / scale); }
        Vector2 operator/(const Vector2& rhs) const { return Vector2(X / rhs.X, Y / rhs.Y); }
        Vector2& operator/=(const T scale) { X /= scale; Y /= scale; return *this; }
        bool operator==(const Vector2& rhs) const { return (X == rhs.X) && (Y == rhs.Y); }
        bool operator!=(const Vector2& rhs) const { return (X != rhs.X) && (Y != rhs.Y); }

        template <typename U> Vector2 operator-(const Vector2<U>& rhs) const { return Vector2(static_cast<T>(X - rhs.X), static_cast<T>(Y - rhs.Y)); }
        template <typename U> Vector2 operator+(const Vector2<U>& rhs) const { return Vector2(static_cast<T>(X + rhs.X), static_cast<T>(Y + rhs.Y)); }
        template <typename U> Vector2 operator*(const Vector2<U>& rhs) const { return Vector2(static_cast<T>(X * rhs.X), static_cast<T>(Y * rhs.Y)); }
        template <typename U> Vector2 operator/(const Vector2<U>& rhs) const { return Vector2(static_cast<T>(X / rhs.X), static_cast<T>(Y / rhs.Y)); }

        std::string ToString() const { return "Vector2(" + std::to_string(X) + ", " + std::to_string(Y) + ")"; }

        static Vector2 One() { return {1, 1}; }
        static Vector2 Zero() { return {0, 0}; }

        static Vector2 Lerp(const Vector2& start, const Vector2& end, const float factor)
        {
            const T x = start.X + (end.X - start.X) * factor;
            const T y = start.Y + (end.Y - start.Y) * factor;
            return { x, y };
        }
    };

    using Vector2I = Vector2<int>;
    using Vector2F = Vector2<float>;
    using Vector2U = Vector2<unsigned>;
    using Vector2D = Vector2<double>;
}
#endif //VECTOR2_H
