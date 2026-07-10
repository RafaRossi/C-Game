//
// Created by rossi on 09/07/2026.
//

#ifndef SDLPROJECT_COLOR_H
#define SDLPROJECT_COLOR_H


#include <SDL3/SDL_pixels.h>

struct Color {
    float r, g, b, a;

    Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}

    Color(float red, float green, float blue, float alpha = 1.0f)
            : r(red), g(green), b(blue), a(alpha) {}

        SDL_Color ToSDLColor() const {
            return {
                    static_cast<Uint8>(r * 255.0f),
                    static_cast<Uint8>(g * 255.0f),
                    static_cast<Uint8>(b * 255.0f),
                    static_cast<Uint8>(a * 255.0f)
            };
    }
};
#endif //SDLPROJECT_COLOR_H
