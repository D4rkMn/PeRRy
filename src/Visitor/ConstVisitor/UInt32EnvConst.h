#ifndef UINT32ENVCONST_H
#define UINT32ENVCONST_H

#include "Visitor/ConstVisitor/IEnvConst.h"

class UInt32EnvConst : public IEnvConst {
public:
    uint32_t value;
    UInt32EnvConst(uint32_t value) : value(value) {}
    ~UInt32EnvConst() = default;
    VarType getType() const override { return VarType::UINT32_TYPE; }
};

#endif