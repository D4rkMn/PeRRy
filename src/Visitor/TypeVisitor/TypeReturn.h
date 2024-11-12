#ifndef TYPERETURN_H
#define TYPERETURN_H

#include "Visitor/IVisitorReturn.h"
#include "Utility/VarType.h"

class TypeReturn : public IVisitorReturn {
public:
    VarType varType;
    TypeReturn(VarType varType) : varType(varType) {}
    ~TypeReturn() = default;
    Type getType() const override { return TYPE_RETURN; }
};

#endif