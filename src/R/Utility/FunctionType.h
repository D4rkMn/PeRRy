#ifndef R_FUNCTIONTYPE_H
#define R_FUNCTIONTYPE_H

#include "R/Utility/VarType.h"
#include "R/Namespace.h"
#include <list>
#include <iostream>

class R::FunctionType {
public:
    VarType returnType;
    std::list<VarType> params;
    FunctionType(VarType, ParamDecList*);
    ~FunctionType() = default;
};

#endif