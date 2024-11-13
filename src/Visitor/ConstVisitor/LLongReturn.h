#ifndef LLONGRETURN_H
#define LLONGRETURN_H

#include "Visitor/IVisitorReturn.h"
#include "Utility/VarType.h"

class LLongReturn : public IVisitorReturn {
public:
    long long value;
    LLongReturn(long long value) : value(value) {}
    ~LLongReturn() = default;
    Type getType() const override { return LLONG_RETURN; }
};

#endif