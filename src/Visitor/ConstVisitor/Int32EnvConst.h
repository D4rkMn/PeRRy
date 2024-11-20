#ifndef INT32ENVCONST_H
#define INT32ENVCONST_H

#include "Visitor/ConstVisitor/IEnvConst.h"

class Int32EnvConst : public IEnvConst {
public:
    int32_t value;
    Int32EnvConst(int32_t value) : value(value) {}
    ~Int32EnvConst() = default;
    VarType getType() const override { return VarType::INT32_TYPE; }
};

#endif