#include "R/Utility/EnvVariable.h"
using namespace std;

R::EnvVariable::EnvVariable(DeclaredType declType, VarType varType, bool mut)
    : declType(declType), varType(varType), mut(mut) {}