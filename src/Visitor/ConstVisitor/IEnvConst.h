#ifndef IENVCONST_H
#define IENVCONST_H

#include "Utility/VarType.h"

class IEnvConst {
public:
    virtual ~IEnvConst() = default;
    virtual VarType getType() const = 0;
};

#endif