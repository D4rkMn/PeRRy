#ifndef INT64ENVCONST_H
#define INT64ENVCONST_H

#include "Visitor/ConstVisitor/IEnvConst.h"

class Int64EnvConst : public IEnvConst {
public:
    long long value;
    Int64EnvConst(long long value) : value(value) {}
    ~Int64EnvConst() = default;
    VarType getType() const override { return VarType::INT64_TYPE; }
};

#endif