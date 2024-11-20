#ifndef INT64ENVCONST_H
#define INT64ENVCONST_H

#include "Visitor/ConstVisitor/IEnvConst.h"

class Int64EnvConst : public IEnvConst {
public:
    int64_t value;
    Int64EnvConst(int64_t value) : value(value) {}
    ~Int64EnvConst() = default;
    VarType getType() const override { return VarType::INT64_TYPE; }
};

#endif