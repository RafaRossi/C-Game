//
// Created by rossi on 06/07/2026.
//

#ifndef SDLPROJECT_COMPONENTFACTORY_H
#define SDLPROJECT_COMPONENTFACTORY_H

#pragma once
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <functional>

class Component;

class ComponentFactory{
public:
    static std::map<std::string, std::function<Component*()>>& GetRegistry(){
        static std::map<std::string, std::function<Component*()>> registry;
        return registry;
    }

    static void Register(const std::string& name, std::function<Component*()> creator) {
        GetRegistry()[name] = std::move(creator);
    }

    static Component* Create(const std::string& name){
        auto it = GetRegistry().find(name);
        if(it != GetRegistry().end()){
            return it->second();
        }
        return nullptr;
    }
};

#endif //SDLPROJECT_COMPONENTFACTORY_H
