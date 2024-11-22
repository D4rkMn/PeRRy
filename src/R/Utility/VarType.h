#ifndef R_VARTYPE_H
#define R_VARTYPE_H

#include <string>
#include "R/Namespace.h"

namespace R {
    enum class VarType {
        INT32_TYPE,
        INT64_TYPE,
        UINT32_TYPE,
        UINT64_TYPE,
        BOOL_TYPE,
        VOID_TYPE,
        UNKNOWN_TYPE
    };
}

std::string varTypeToString(R::VarType);

#endif