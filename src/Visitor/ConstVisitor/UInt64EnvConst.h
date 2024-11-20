#ifndef UINT64ENVCONST_H
#define UINT64ENVCONST_H

#include "Visitor/ConstVisitor/IEnvConst.h"

class UInt64EnvConst : public IEnvConst {
public:
    uint64_t value;
    UInt64EnvConst(uint64_t value) : value(value) {}
    ~UInt64EnvConst() = default;
    VarType getType() const override { return VarType::UINT64_TYPE; }
};

#endif