#include <iostream>
#include "ASTNodes/Exp.h"
using namespace std;

string Exp::binopToString(BinaryOp op) {
    string s;
    switch(op) {
        // Arithmetic operators
        case PLUS_OP: s = "+"; break;
        case MINUS_OP: s = "-"; break;
        case MUL_OP: s = "*"; break;
        case DIV_OP: s = "/"; break;
        // Boolean operators
        case LESS_OP: s = "<"; break;
        case LESS_EQ_OP: s = "<="; break;
        case EQUALS_OP: s = "=="; break;
        case GREATER_OP: s = ">"; break;
        case GREATER_EQ_OP: s = ">="; break;
        case NEQUALS_OP: s = "!="; break;
        default: s = "$";
    }
    return s;
}

// BinaryExp

BinaryExp::BinaryExp(Exp* l, Exp* r, BinaryOp op) : left(l), right(r), op(op) {}
BinaryExp::~BinaryExp() {
    if (left) delete left;
    if (right) delete right;
}

// IntegerExp

IntegerExp::IntegerExp(int32_t v) {
    if (v <= INT32_MAX && v >= INT32_MIN) {
        value = uint32_t(v);
        type = VarType::INT32_TYPE;
    }
    string msg = "Error: El entero con valor '" + to_string(v) + "' se le intentó asignar el tipo 'i32'";
    throw runtime_error(msg);
}

IntegerExp::IntegerExp(uint64_t v, VarType type) : value(v), type(type) {
    if (value >= 2147483648 && type != VarType::INT64_TYPE) {
        string msg = "Error: El entero con valor '" + to_string(value) + "' se le intentó asignar el tipo '" + varTypeToString(type) + "'";
        throw runtime_error(msg);
    }
    if (type == VarType::INT32_TYPE && (value < INT32_MIN || value > INT32_MAX)) {

    }
}

// IdentifierExp

IdentifierExp::IdentifierExp(const string& n) : name(n) {}

// FunctionExp

FunctionExp::FunctionExp(const string& n) : name(n) {}

FunctionExp::~FunctionExp() {
    for (auto it = args.begin(); it != args.end(); it++) {
        if (*it) delete *it;
    }
}