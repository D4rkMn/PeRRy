#ifndef LLONGRETURN_H
#define LLONGRETURN_H

#include "Visitor/IVisitorReturn.h"
#include "Utility/VarType.h"

class LLongReturn : public IVisitorReturn {
public:
    uint64_t value;
    LLongReturn(uint64_t value) : value(value) {}
    ~LLongReturn() = default;
    Type getType() const override { return LLONG_RETURN; }
};

#endif