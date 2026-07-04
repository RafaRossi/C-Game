//
// Created by rossi on 02/07/2026.
//

#ifndef SDLPROJECT_REFLECTION_H
#define SDLPROJECT_REFLECTION_H

#pragma once
#include <string>
#include <vector>
#include <functional>
#include <cstddef>
#include <unordered_map>

enum class PropertyType {
    Int,
    Float,
    Bool,
    Vector2,
    String
};

struct Property {
    std::string Name;
    PropertyType Type;
    size_t Offset;
};

struct ClassMetadata{
    std::string ClassName;
    std::vector<Property> Properties;
};

#define BEGIN_REFLECTION(Classe) \
void RegisterReflection_##Classe(ClassMetadata& meta){ \
    meta.ClassName = #Classe;

#define PROPERTY(Classe, Tipo, Variavel) \
meta.Properties.push_back({#Variavel, PropertyType::Tipo, offsetof(Classe, Variavel)});
#define END_REFLECTION(Classe)                              \
}                                                           \
struct Classe##AutoRegister {                               \
    Classe##AutoRegister() {                                \
        GlobalRegistry()[#Classe] = RegisterReflection_##Classe; \
    }                                                       \
};                                                          \
static Classe##AutoRegister Classe##AutoRegister_Instance;

using RegisterFn = std::function<void(ClassMetadata&)>;

inline std::unordered_map<std::string , RegisterFn>& GlobalRegistry(){
    static std::unordered_map<std::string, RegisterFn> registry;
    return registry;
}

inline ClassMetadata GetMetadata(const std::string& className){
    ClassMetadata meta;
    auto it = GlobalRegistry().find(className);
    if(it != GlobalRegistry().end())
        it->second(meta);
    return meta;
}

#endif //SDLPROJECT_REFLECTION_H

