#ifndef SDLPROJECT_COLOR_H
#define SDLPROJECT_COLOR_H

#include <SDL3/SDL_pixels.h>

struct Color32;

struct Color {
    float r, g, b, a;

    constexpr Color() : r(255.0f), g(255.0f), b(255.0f), a(255.0f) {}
    constexpr Color(float r, float g, float b, float a = 255.0f) : r(r), g(g), b(b), a(a) {}

    constexpr Color(const Color32& c32);

    static constexpr Color White()       { return {255.0f, 255.0f, 255.0f, 255.0f}; }
    static constexpr Color Black()       { return {0.0f, 0.0f, 0.0f, 255.0f}; }
    static constexpr Color Red()         { return {255.0f, 0.0f, 0.0f, 255.0f}; }
    static constexpr Color Green()       { return {0.0f, 255.0f, 0.0f, 255.0f}; }
    static constexpr Color Blue()        { return {0.0f, 0.0f, 255.0f, 255.0f}; }
    static constexpr Color Yellow()      { return {255.0f, 255.0f, 0.0f, 255.0f}; }
    static constexpr Color Cyan()        { return {0.0f, 255.0f, 255.0f, 255.0f}; }
    static constexpr Color Magenta()     { return {255.0f, 0.0f, 255.0f, 255.0f}; }
    static constexpr Color Transparent() { return {0.0f, 0.0f, 0.0f, 0.0f}; }
    static constexpr Color Slate()       { return {99.0f, 115.0f, 140.0f, 255.0f}; }
    static constexpr Color Gray()        { return {107.0f, 115.0f, 128.0f, 255.0f}; }
    static constexpr Color Zinc()        { return {112.0f, 112.0f, 122.0f, 255.0f}; }
    static constexpr Color Emerald()     { return {15.0f, 186.0f, 130.0f, 255.0f}; }
    static constexpr Color Sky()         { return {13.0f, 166.0f, 232.0f, 255.0f}; }
    static constexpr Color Indigo()      { return {99.0f, 102.0f, 242.0f, 255.0f}; }
    static constexpr Color Rose()        { return {245.0f, 64.0f, 94.0f, 255.0f}; }
    static constexpr Color Amber()       { return {245.0f, 158.0f, 10.0f, 255.0f}; }
    static constexpr Color Fuchsia()     { return {191.0f, 38.0f, 176.0f, 255.0f}; }
};

struct Color32 {
    Uint8 r, g, b, a;

    constexpr Color32() : r(255), g(255), b(255), a(255) {}
    constexpr Color32(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) : r(r), g(g), b(b), a(a) {}

    constexpr Color32(const Color& c) :
            r(static_cast<Uint8>(c.r)),
            g(static_cast<Uint8>(c.g)),
            b(static_cast<Uint8>(c.b)),
            a(static_cast<Uint8>(c.a)) {}
};

inline constexpr Color::Color(const Color32& c32) :
        r(static_cast<float>(c32.r)),
        g(static_cast<float>(c32.g)),
        b(static_cast<float>(c32.b)),
        a(static_cast<float>(c32.a)) {}

#endif //SDLPROJECT_COLOR_H