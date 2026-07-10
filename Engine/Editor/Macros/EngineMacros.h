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
#define REGISTER_BODY(ClassName, BaseClassName)                                \
    public:                                                                    \
    std::string GetTypeName() const override { return #ClassName; }            \
    BaseClassName* Clone() const override { return new ClassName(*this); }     \
    void AutoExposeField(FieldCollector& collector) override;
#else
#define REGISTER_BODY(ClassName, BaseClassName)                                 \
    public:                                                                     \
    std::string GetTypeName() const override { return #ClassName; }             \
    BaseClassName* Clone() const override { return new ClassName(*this); }
#endif

#endif //SDLPROJECT_ENGINEMACROS_H
