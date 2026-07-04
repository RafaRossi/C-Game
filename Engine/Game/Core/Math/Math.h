//
// Created by rossi on 29/06/2026.
//

#ifndef SDLPROJECT_MATH_H
#define SDLPROJECT_MATH_H

#include <cmath>
#include <algorithm>
#include <numbers>

namespace Math {
    constexpr float PI = std::numbers::pi_v<float>;

    inline float Lerp(float a, float b, float t){
        return a + (b - a) * t;
    }

    inline float Clamp(float value, float min, float max)
    {
        return std::clamp(value, min, max);
    }

    inline float Clamp01(float value){
        return std::clamp(value, 0.0f, 1.0f);
    }

    inline float SmoothStep(float a, float b, float t){
        t = Clamp01(t);
        t = t * t * (3.0f - 2.0f * t);
        return Lerp(a, b, t);
    }
}

#endif //SDLPROJECT_MATH_H
