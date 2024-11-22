#include <iostream>
#include "R/ASTNodes/Exp.h"
#include "R/Utility/NumberTester.h"
using namespace std;

string R::Exp::binopToString(R::BinaryOp op) {
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

string R::Exp::unopToString(R::UnaryOp op) {
    string s;
    switch(op) {
        // Arithmetic operators
        case NEG_OP: s = "-"; break;
        // Boolean operators
        case NOT_OP: s = "!"; break;
    }
    return s;
}

// BinaryExp

R::BinaryExp::BinaryExp(Exp* l, Exp* r, BinaryOp op) : left(l), right(r), op(op) {}
R::BinaryExp::~BinaryExp() {
    if (left) delete left;
    if (right) delete right;
}

// UnaryExp

R::UnaryExp::UnaryExp(Exp* exp, UnaryOp op) : exp(exp), op(op) {}
R::UnaryExp::~UnaryExp() {
    if (exp) delete exp;
}

// IntegerExp

R::IntegerExp::IntegerExp(const string& s) {
    if (NumberTester::fitsInInt32(s)) {
        value = int32_t(stoi(s));
        type = VarType::INT32_TYPE;
        isImplicit = true;
        return;
    }
    string msg = "Error: El entero con valor '" + s + "' se le intentó asignar el tipo 'i32'";
    throw runtime_error(msg);
}

R::IntegerExp::IntegerExp(const string& s, VarType type) : type(type) {
    if (type == VarType::INT32_TYPE && NumberTester::fitsInInt32(s)) {
        value = int32_t(stoi(s));
        return;
    }
    if (type == VarType::INT64_TYPE && NumberTester::fitsInInt64(s)) {
        value = int64_t(stoll(s));
        return;
    }
    if (type == VarType::UINT32_TYPE && NumberTester::fitsInUInt32(s)) {
        value = uint32_t(stoul(s));
        return;
    }
    if (type == VarType::UINT64_TYPE && NumberTester::fitsInUInt64(s)) {
        value = uint64_t(stoull(s));
        return;
    }
    string msg = "Error: El entero con valor '" + s + "' se le intentó asignar el tipo '" + varTypeToString(type) + "'";
    throw runtime_error(msg);
}

R::IntegerExp::IntegerExp(int32_t v) {
    type = VarType::INT32_TYPE;
    value = int32_t(v);
}

R::IntegerExp::IntegerExp(int64_t v) {
    type = VarType::INT64_TYPE;
    value = int64_t(v);
}

R::IntegerExp::IntegerExp(uint32_t v) {
    type = VarType::UINT32_TYPE;
    value = uint32_t(v);
}

R::IntegerExp::IntegerExp(uint64_t v) {
    type = VarType::UINT64_TYPE;
    value = uint64_t(v);
}

R::IntegerExp::IntegerExp(bool v) {
    type = VarType::BOOL_TYPE;
    value = bool(v);
}

// IdentifierExp

R::IdentifierExp::IdentifierExp(const string& n) : name(n) {}

// FunctionExp

R::FunctionExp::FunctionExp(const string& n) : name(n) {}

R::FunctionExp::~FunctionExp() {
    for (auto it = args.begin(); it != args.end(); it++) {
        if (*it) delete *it;
    }
}