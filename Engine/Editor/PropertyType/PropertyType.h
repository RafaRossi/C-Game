//
// Created by rossi on 06/07/2026.
//

#ifndef SDLPROJECT_PROPERTYTYPE_H
#define SDLPROJECT_PROPERTYTYPE_H

#include <string>
#include <vector>
#include "../../Game/Core/Math/Vector2.h"

enum class PropertyType {
    Int,
    Float,
    Bool,
    Vector2,
    String
};

struct ExposedField {
    std::string Name;
    PropertyType Type;
    void* Ptr;
};

class FieldCollector {
public:
    void Expose(const std::string& name, int* v)         { m_Fields.push_back({name, PropertyType::Int, v}); }
    void Expose(const std::string& name, float* v)       { m_Fields.push_back({name, PropertyType::Float, v}); }
    void Expose(const std::string& name, bool* v)        { m_Fields.push_back({name, PropertyType::Bool, v}); }
    void Expose(const std::string& name, Vector2* v)     { m_Fields.push_back({name, PropertyType::Vector2, v}); }
    void Expose(const std::string& name, std::string* v) { m_Fields.push_back({name, PropertyType::String, v}); }

    const std::vector<ExposedField>& GetFields() const { return m_Fields; }

private:
    std::vector<ExposedField> m_Fields;
};
#endif //SDLPROJECT_PROPERTYTYPE_H
