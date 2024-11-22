#ifndef R_REDUCEDRETURN_H
#define R_REDUCEDRETURN_H

#include "R/Visitor/IVisitorReturn.h"
#include "R/Namespace.h"

class R::ReducedReturn : public IVisitorReturn {
public:
    IntegerExp* exp;
    ReducedReturn(IntegerExp* exp) : exp(exp) {}
    ~ReducedReturn() = default;
    Type getType() const override { return REDUCE_RETURN; }
};

#endif