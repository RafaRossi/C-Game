//
// Created by rossi on 26/07/2026.
//

#ifndef SDLPROJECT_LEVELROOM_H
#define SDLPROJECT_LEVELROOM_H

#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_log.h>
#include "Engine/Game/Core/Math/Vector2.h"
#include "Sandbox/Assets/Premades/Premades.h"
#include "Sandbox/Assets/Scripts/Player.h"
#include "Engine/Game/Core/Renderer/Renderer.h"
#include "Engine/Game/Core/Collision/BoxCollider.h"

constexpr int Tile_Size_Width = 32;
constexpr int Tile_Size_Height = 32;

class Level
{

public:
    int Width()  const { return m_Width; }
    int Height() const { return m_Height; }

    const std::vector<Vector2>& PlayerSpawnPoints() const { return m_PlayerSpawnPoints; }

    virtual Level* GenerateLevel(const char* filePath, int scale = 1)
    {
        SDL_Surface* surface = SDL_LoadBMP(filePath);
        if (!surface) {
            SDL_Log("Erro ao carregar mapa: %s", SDL_GetError());
            return nullptr;
        }

        SDL_Surface* formattedSurface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        SDL_DestroySurface(surface);

        auto* pixels = (Uint32*)formattedSurface->pixels;
        m_Width = formattedSurface->w;
        m_Height = formattedSurface->h;

        m_PlayerSpawnPoints.clear();

        const SDL_PixelFormatDetails* details = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA32);


        for (int y = 0; y < m_Height; y++) {
            for (int x = 0; x < m_Width; x++) {
                Uint32 pixel = pixels[y * m_Width + x];

                Uint8 r, g, b, a;
                SDL_GetRGBA(pixel, details, nullptr, &r, &g, &b, &a);

                Vector2 worldPos = { static_cast<float>(x * Tile_Size_Width * scale), static_cast<float>(y * Tile_Size_Height * scale) };

                if (r == 255 && g == 0 && b == 0) {
                    auto* wall = Premades::GenericActor("Wall", nullptr, worldPos, 0.f);

                    auto* rigidbody = wall->AddComponent<Rigidbody>(RigidbodyType::Static);
                    auto size = Vector2(Tile_Size_Width * scale, Tile_Size_Height * scale);

                    wall->AddComponent<Renderer>(Color::Amber(), size);
                    wall->AddComponent<BoxCollider>(rigidbody, size);
                }
                else if(r == 0 && g == 0 && b == 255) {
                    m_PlayerSpawnPoints.push_back(worldPos);
                }
            }
        }

        SDL_DestroySurface(formattedSurface);

        return this;
    }

private:
    int m_Width = 255;
    int m_Height = 255;

    std::vector<Vector2> m_PlayerSpawnPoints;
};

#endif //SDLPROJECT_LEVELROOM_H
