//
// Created by rossi on 09/07/2026.
//

#ifndef SDLPROJECT_SCENESERIALIZER_H
#define SDLPROJECT_SCENESERIALIZER_H

#include <string>

class Scene;

class SceneSerializer {
public:
    static void SaveScene(Scene* scene, const std::string& path);
    static bool LoadScene(Scene* scene, const std::string& path);
};


#endif //SDLPROJECT_SCENESERIALIZER_H
