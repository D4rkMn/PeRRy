#ifndef VARTYPE_H
#define VARTYPE_H

#include <string>

enum class VarType {
    INT32_TYPE,
    INT64_TYPE,
    VOID_TYPE,
    UNKNOWN_TYPE
};

std::string varTypeToString(VarType);

#endif