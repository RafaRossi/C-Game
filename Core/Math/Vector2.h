//
// Created by rossi on 29/06/2026.
//

#ifndef SDLPROJECT_VECTOR2_H
#define SDLPROJECT_VECTOR2_H

#include "Math.h"

#include <SDL3/SDL_rect.h>

struct Vector2{
    float x = 0.0f;
    float y = 0.0f;

    Vector2() = default;
    Vector2(float x, float y) : x(x), y(y) {}

    operator SDL_FPoint() const { return {x, y}; }

    Vector2 operator+(const Vector2& other) const { return {x + other.x, y + other.y}; }
    Vector2 operator-(const Vector2& other) const { return {x - other.x, y - other.y}; }
    Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }

    Vector2 operator/(float scalar) const { return {x / scalar, y / scalar }; }
    Vector2 operator-() const { return {-x, -y }; }

    friend Vector2 operator*(float scalar, const Vector2& v){
        return {v.x * scalar, v.y * scalar};
    }

    inline float Length() const {
        return std::sqrt(x * x + y * y);
    }

    inline Vector2 Normalized() const {
        float len = Length();
        if(len == 0.0f) return {0.0f, 0.0f};
        return {x / len, y / len };
    }

    static Vector2 Lerp(Vector2 a, Vector2 b, float t){
        return {
            Math::Lerp(a.x, b.x, t), Math::Lerp(a.y, b.y, t)
        };
    }

    static float Dot(Vector2 a, Vector2 b){
        return a.x * b.x + a.y * b.y;
    }
};

#endif //SDLPROJECT_VECTOR2_H
