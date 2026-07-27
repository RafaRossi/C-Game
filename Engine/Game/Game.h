#ifndef SDLPROJECT_GAME_H
#define SDLPROJECT_GAME_H

#pragma once

#include <random>
#include <SDL3/SDL.h>
#include <vector>
#include <algorithm>
#include "Core/Actor/Actor.h"
#include "Core/Camera/CameraComponent.h"
#include "Core/Scene/Scene.h"
#include <stdexcept>


class Game {
public:
    static Game& Instance(){
        static Game instance;
        return instance;
    }

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void Init(Scene *scene, SDL_Renderer* renderer);

    void SetSeed(unsigned int seed);
    void GenerateRandomSeed();

    unsigned int GetCurrentSeed() const { return m_CurrentSeed; }
    std::mt19937& GetRNG() { return m_Rng; }

    int GetRandomInt(int min, int max);
    float GetRandomFloat(float min, float max);

    template <typename T>
    static std::optional<T> GetRandomElement(const std::vector<T>& vectorList) {
        if (vectorList.empty()) {
            return std::nullopt;
        }

        std::uniform_int_distribution<size_t> dis(0, vectorList.size() - 1);

        size_t randomIndex = dis(Game::Instance().GetRNG());

        return vectorList[randomIndex];
    }

    void ProcessEvents(SDL_Event event);

    void Start();

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);

    Actor* CreateActor(const std::string& actorName);

    void Render();
    void Shutdown();

    SDL_Renderer* GetRenderer() { return m_Renderer; }
    Scene* GetScene() { return m_Scene; }

private:
    Game() = default;
    ~Game() = default;

    SDL_Renderer* m_Renderer    = nullptr;
    Scene*        m_Scene = nullptr;

    bool          m_IsRunning   = false;

    unsigned int m_CurrentSeed = 0;
    std::mt19937 m_Rng;
};

#endif