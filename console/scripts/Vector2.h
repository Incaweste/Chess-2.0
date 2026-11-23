#pragma once

#include <cmath>

class Vector2
{
public:
    int row = 0;
    int col = 0;
public:
    Vector2() noexcept = default;
    constexpr Vector2(int row, int col) noexcept : row{row}, col{col} 
    {
    }

    constexpr Vector2 operator-() const noexcept
    {
        return Vector2{-row, -col};
    }

    constexpr Vector2& operator+=(const Vector2& other) noexcept
    {
        row += other.row;
        col += other.col;
        return *this;
    }

    constexpr Vector2& operator-=(const Vector2& other) noexcept
    {
        row -= other.row;
        col -= other.col;
        return *this;
    }

    constexpr Vector2& operator*=(int other) noexcept
    {
        row *= other;
        col *= other;
        return *this;
    }

    constexpr Vector2& operator/=(int other)
    {
        row /= other;
        col /= other;
        return *this;
    }

    float GetVectorLength() const noexcept
    {
        return std::sqrtf(static_cast<float>(row * row + col * col));
    }

    friend constexpr Vector2 operator+(Vector2 first, const Vector2& second) noexcept
    {
        return first += second;
    }

    friend constexpr Vector2 operator-(Vector2 first, const Vector2& second) noexcept
    {
        return Vector2{first.row - second.row, first.col - second.col};
    }

    friend constexpr Vector2 operator*(Vector2 vector, int factor) noexcept
    {
        return vector *= factor;
    }

    friend constexpr Vector2 operator/(Vector2 vector, int factor)
    {
        return vector /= factor;
    }
};