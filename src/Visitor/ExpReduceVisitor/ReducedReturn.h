#ifndef REDUCEDRETURN_H
#define REDUCEDRETURN_H

#include "Visitor/IVisitorReturn.h"

class IntegerExp;

class ReducedReturn : public IVisitorReturn {
public:
    IntegerExp* exp;
    ReducedReturn(IntegerExp* exp) : exp(exp) {}
    ~ReducedReturn() = default;
    Type getType() const override { return REDUCE_RETURN; }
};

#endif