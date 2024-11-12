#ifndef ENVVARIABLE_H
#define ENVVARIABLE_H

#include "Utility/VarType.h"

class EnvVariable {
public:

    enum DeclaredType {
        CONST_VAR,
        STATIC_VAR,
        LET_VAR
    };

    DeclaredType declType;
    VarType varType;
    bool mut;

    EnvVariable() = default;
    EnvVariable(DeclaredType, VarType, bool);
    ~EnvVariable() = default;
};

#endif