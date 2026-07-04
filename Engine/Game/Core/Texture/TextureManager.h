//
// Created by rossi on 01/07/2026.
//

#ifndef SDLPROJECT_TEXTUREMANAGER_H
#define SDLPROJECT_TEXTUREMANAGER_H


#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>
#include <SDL3/SDL_log.h>
#include <unordered_map>

class TextureManager {
public:
    static TextureManager& Instance(){
        static TextureManager instance;
        return instance;
    }

    void Init(SDL_Renderer* renderer){
        m_Renderer = renderer;
    }

    SDL_Texture* Load(const std::string& path){
        auto it = m_Cache.find(path);
        if(it != m_Cache.end())
            return it->second;

        SDL_Texture* texture = IMG_LoadTexture(m_Renderer, path.c_str());
        if(texture == nullptr){
            SDL_Log("Texture Manager: falaha ao carregar '%s' : %s", path.c_str(), SDL_GetError());
            return nullptr;
        }

        m_Cache[path] = texture;
        return texture;
    }

    void Unload(const std::string& path){
        auto it = m_Cache.find(path);
        if(it != m_Cache.end()){
            SDL_DestroyTexture(it->second);
            m_Cache.erase(it);
        }
    }

    void UnloadAll(){
        for(auto& [path, texture] : m_Cache)
            SDL_DestroyTexture(texture);
        m_Cache.clear();
    }

private:
    TextureManager() = default;

    SDL_Renderer* m_Renderer;
    std::unordered_map<std::string, SDL_Texture*> m_Cache;
};


#endif //SDLPROJECT_TEXTUREMANAGER_H
