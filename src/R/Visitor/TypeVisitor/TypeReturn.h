#ifndef R_TYPERETURN_H
#define R_TYPERETURN_H

#include "R/Visitor/IVisitorReturn.h"
#include "R/Utility/VarType.h"
#include "R/Namespace.h"

class R::TypeReturn : public IVisitorReturn {
public:
    VarType varType;
    TypeReturn(VarType varType) : varType(varType) {}
    ~TypeReturn() = default;
    Type getType() const override { return TYPE_RETURN; }
};

#endif