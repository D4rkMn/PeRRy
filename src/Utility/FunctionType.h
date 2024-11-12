#ifndef FUNCTIONTYPE_H
#define FUNCTIONTYPE_H

#include "Utility/VarType.h"
#include <list>
#include <iostream>

class ParamDecList;

class FunctionType {
public:
    VarType returnType;
    std::list<VarType> params;
    FunctionType(VarType, ParamDecList*);
    ~FunctionType() = default;
};

#endif