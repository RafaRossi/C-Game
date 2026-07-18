#ifndef SDLPROJECT_COLOR_H
#define SDLPROJECT_COLOR_H

#include <SDL3/SDL_pixels.h>

struct Color32;

struct Color {
    float r, g, b, a;

    constexpr Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
    constexpr Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}

    constexpr Color(const Color32& c32);

    static constexpr Color White()       { return {1.0f, 1.0f, 1.0f, 1.0f}; }
    static constexpr Color Black()       { return {0.0f, 0.0f, 0.0f, 1.0f}; }
    static constexpr Color Red()         { return {1.0f, 0.0f, 0.0f, 1.0f}; }
    static constexpr Color Green()       { return {0.0f, 1.0f, 0.0f, 1.0f}; }
    static constexpr Color Blue()        { return {0.0f, 0.0f, 1.0f, 1.0f}; }
    static constexpr Color Yellow()      { return {1.0f, 1.0f, 0.0f, 1.0f}; }
    static constexpr Color Cyan()        { return {0.0f, 1.0f, 1.0f, 1.0f}; }
    static constexpr Color Magenta()     { return {1.0f, 0.0f, 1.0f, 1.0f}; }
    static constexpr Color Transparent() { return {0.0f, 0.0f, 0.0f, 0.0f}; }
    static constexpr Color Slate()       { return {0.39f, 0.45f, 0.55f, 1.0f}; }
    static constexpr Color Gray()        { return {0.42f, 0.45f, 0.50f, 1.0f}; }
    static constexpr Color Zinc()        { return {0.44f, 0.44f, 0.48f, 1.0f}; }
    static constexpr Color Emerald()     { return {0.06f, 0.73f, 0.51f, 1.0f}; }
    static constexpr Color Sky()         { return {0.05f, 0.65f, 0.91f, 1.0f}; }
    static constexpr Color Indigo()      { return {0.39f, 0.40f, 0.95f, 1.0f}; }
    static constexpr Color Rose()        { return {0.96f, 0.25f, 0.37f, 1.0f}; }
    static constexpr Color Amber()       { return {0.96f, 0.62f, 0.04f, 1.0f}; }
    static constexpr Color Fuchsia()     { return {0.75f, 0.15f, 0.69f, 1.0f}; }
};

struct Color32 {
    Uint8 r, g, b, a;

    constexpr Color32() : r(255), g(255), b(255), a(255) {}
    constexpr Color32(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) : r(r), g(g), b(b), a(a) {}

    constexpr Color32(const Color& c) :
            r(static_cast<Uint8>(c.r * 255.0f)),
            g(static_cast<Uint8>(c.g * 255.0f)),
            b(static_cast<Uint8>(c.b * 255.0f)),
            a(static_cast<Uint8>(c.a * 255.0f)) {}
};

inline constexpr Color::Color(const Color32& c32) :
        r(c32.r / 255.0f),
        g(c32.g / 255.0f),
        b(c32.b / 255.0f),
        a(c32.a / 255.0f) {}

#endif //SDLPROJECT_COLOR_H