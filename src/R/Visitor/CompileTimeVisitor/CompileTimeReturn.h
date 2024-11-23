#ifndef R_COMPILETIMERETURN_H
#define R_COMPILETIMERETURN_H

#include "R/Visitor/IVisitorReturn.h"

class R::CompileTimeReturn : public IVisitorReturn {
public:
    CompileTimeReturn() = default;
    ~CompileTimeReturn() = default;
    Type getType() const override { return COMPILETIME_RETURN; }
};

#endif