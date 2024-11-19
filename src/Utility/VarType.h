#ifndef VARTYPE_H
#define VARTYPE_H

#include <string>

enum class VarType {
    INT32_TYPE,
    INT64_TYPE,
    UINT32_TYPE,
    UINT64_TYPE,
    BOOL_TYPE,
    VOID_TYPE,
    UNKNOWN_TYPE
};

std::string varTypeToString(VarType);

#endif