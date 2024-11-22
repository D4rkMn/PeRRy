#ifndef R_ENVVARIABLE_H
#define R_ENVVARIABLE_H

#include "R/Utility/VarType.h"
#include "R/Namespace.h"

class R::EnvVariable {
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