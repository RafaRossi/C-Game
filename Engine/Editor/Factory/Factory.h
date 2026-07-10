//
// Created by rossi on 09/07/2026.
//

#ifndef SDLPROJECT_FACTORY_H
#define SDLPROJECT_FACTORY_H

#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

template <typename BaseType>
class Factory{
public:
    using CreatorFunc = std::function<BaseType*()>;

    static void Register(const std::string & name, CreatorFunc creator){
        GetRegistry()[name] = creator;
    }

    static BaseType* Create(const std::string& name){
        if(GetRegistry().find(name) != GetRegistry().end()){
            return GetRegistry()[name]();
        }
        return nullptr;
    }

    static std::unordered_map<std::string, CreatorFunc>& GetRegistry(){
        static std::unordered_map<std::string, CreatorFunc> registry;
        return registry;
    }
};

#endif //SDLPROJECT_FACTORY_H
