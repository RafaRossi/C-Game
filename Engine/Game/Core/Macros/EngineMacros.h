//
// Created by rossi on 05/07/2026.
//

#ifndef SDLPROJECT_ENGINEMACROS_H
#define SDLPROJECT_ENGINEMACROS_H


#pragma once

#ifndef PROPERTY
#define PROPERTY(...)
#endif


#define REGISTER_BODY(ClassName, BaseClassName)                                \
    public:                                                                    \
    std::string GetTypeName() const override { return #ClassName; }            \
    BaseClassName* Clone() const override { return new ClassName(*this); }     \
    void AutoExposeField(FieldCollector& collector) override;

#define INSTANCED(ClassName) \
    public: \
    virtual ~ClassName() = default; \
    virtual std::string GetTypeName() const = 0; \
    virtual ClassName* Clone() const = 0; \
    virtual void AutoExposeField(class FieldCollector& collector) {}


#endif //SDLPROJECT_ENGINEMACROS_H
