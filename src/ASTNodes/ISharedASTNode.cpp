#include "ASTNodes/ISharedASTNode.h"
#include <iostream>
using namespace std;

string varTypeToString(VarType type) {
    string s = "";
    switch (type) {
        case INT32_TYPE: s = "i32"; break;
        case INT64_TYPE: s = "i64"; break;
        case VOID_TYPE: s = "This message should not appear. What should I do if it does...?"; break;
        case UNKNOWN_TYPE: s = "This message should not appear. I'll be sacred if it does..."; break;
        default: s = "This message should not appear. If it does, it's a bug."; break;
    }
    return s;
}