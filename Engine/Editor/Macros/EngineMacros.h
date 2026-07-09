//
// Created by rossi on 05/07/2026.
//

#ifndef SDLPROJECT_ENGINEMACROS_H
#define SDLPROJECT_ENGINEMACROS_H


#pragma once

#ifndef PROPERTY
#define PROPERTY(...)
#endif

#ifdef TR_EDITOR
#define COMPONENT_BODY(ClassName) \
    public: \
    std::string GetComponentName() const override { return #ClassName; } \
    Component* Clone() const override { return new ClassName(*this); } \
    void AutoExposeField(FieldCollector& collector) override;
#else
#define COMPONENT_BODY(ClassName) \
    public: \
    std::string GetClassName() const override { return #ClassName; }
    Component* Clone() const override { return new ClassName(*this); }
#endif

#endif //SDLPROJECT_ENGINEMACROS_H
