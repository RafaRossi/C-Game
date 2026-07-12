//
// Created by rossi on 06/07/2026.
//

#ifndef SDLPROJECT_PROPERTYTYPE_H
#define SDLPROJECT_PROPERTYTYPE_H

#include <string>
#include <vector>
#include <functional>
#include "Engine/Game/Core/Math/Vector2.h"
#include "Engine/Game/Core/Color/Color.h"
#include "Engine/Game/Core/Factory/Factory.h"

enum class PropertyType {
    Int,
    Float,
    Bool,
    Vector2,
    String,
    Color,
    Polymorphic
};

struct ExposedField {
    std::string Name;
    PropertyType Type;
    void* Ptr;

    std::vector<std::string> AvailableTypes;
    std::function<void(const std::string&)> InstantiateFunc;
    std::function<std::string()> GetCurrentTypeName;
    std::function<void(class FieldCollector&)> ExposeCurrentObjectFunc;
};

class FieldCollector {
public:
    void Expose(const std::string& name, int* v)         { m_Fields.push_back({name, PropertyType::Int, v}); }
    void Expose(const std::string& name, float* v)       { m_Fields.push_back({name, PropertyType::Float, v}); }
    void Expose(const std::string& name, bool* v)        { m_Fields.push_back({name, PropertyType::Bool, v}); }
    void Expose(const std::string& name, Vector2* v)     { m_Fields.push_back({name, PropertyType::Vector2, v}); }
    void Expose(const std::string& name, std::string* v) { m_Fields.push_back({name, PropertyType::String, v}); }
    void Expose(const std::string& name, Color* v)       { m_Fields.push_back({name, PropertyType::Color, v}); }

    const std::vector<ExposedField>& GetFields() const { return m_Fields; }

    template <typename BaseClass>
    void ExposePolymorphic(const std::string& name, BaseClass** ptrToPtr) {
        ExposedField f;
        f.Name = name;
        f.Type = PropertyType::Polymorphic;
        f.Ptr = nullptr;

        for (const auto& [typeName, creator] : Factory<BaseClass>::GetRegistry()) {
            f.AvailableTypes.push_back(typeName);
        }

        f.InstantiateFunc = [ptrToPtr](const std::string& typeName) {
            if (*ptrToPtr) {
                delete *ptrToPtr;
                *ptrToPtr = nullptr;
            }
            if (typeName != "None") {
                *ptrToPtr = Factory<BaseClass>::Create(typeName);
            }
        };

        f.GetCurrentTypeName = [ptrToPtr]() -> std::string {
            if (*ptrToPtr) return (*ptrToPtr)->GetTypeName();
            return "None";
        };

        f.ExposeCurrentObjectFunc = [ptrToPtr](FieldCollector& nestedCollector) {
            if (*ptrToPtr) (*ptrToPtr)->AutoExposeField(nestedCollector);
        };

        m_Fields.push_back(f);
    }

private:
    std::vector<ExposedField> m_Fields;
};
#endif //SDLPROJECT_PROPERTYTYPE_H
