#include "Utility/EnvVariable.h"
using namespace std;

EnvVariable::EnvVariable(DeclaredType declType, VarType varType, bool mut)
    : declType(declType), varType(varType), mut(mut) {}