#include "R/Utility/VarType.h"
using namespace std;

string varTypeToString(R::VarType type) {
    string s = "";
    switch (type) {
        case R::VarType::INT32_TYPE: s = "i32"; break;
        case R::VarType::INT64_TYPE: s = "i64"; break;
        case R::VarType::UINT32_TYPE: s = "u32"; break;
        case R::VarType::UINT64_TYPE: s = "u64"; break;
        case R::VarType::BOOL_TYPE: s = "bool"; break;
        case R::VarType::VOID_TYPE: s = "void"; break;
        case R::VarType::UNKNOWN_TYPE: s = "This message should not appear. What should I do if it does...?"; break;
        default: s = "This message should not appear. I'll be scared if it does..."; break;
    }
    return s;
}