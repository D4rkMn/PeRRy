#include "Utility/VarType.h"
using namespace std;

string varTypeToString(VarType type) {
    string s = "";
    switch (type) {
        case VarType::INT32_TYPE: s = "i32"; break;
        case VarType::INT64_TYPE: s = "i64"; break;
        case VarType::UINT32_TYPE: s = "u32"; break;
        case VarType::UINT64_TYPE: s = "u64"; break;
        case VarType::BOOL_TYPE: s = "bool"; break;
        case VarType::VOID_TYPE: s = "void"; break;
        case VarType::UNKNOWN_TYPE: s = "This message should not appear. What should I do if it does...?"; break;
        default: s = "This message should not appear. I'll be scared if it does..."; break;
    }
    return s;
}