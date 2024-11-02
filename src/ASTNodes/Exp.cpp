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
BinaryExp::~BinaryExp() { delete left; delete right; }

// IntegerExp

IntegerExp::IntegerExp(int v) : value(v) {}

// IdentifierExp

IdentifierExp::IdentifierExp(const string& n) : name(n) {}

// FunctionExp

FunctionExp::FunctionExp(const string& n) : name(n) {}

FunctionExp::~FunctionExp() {
    for (auto it = args.begin(); it != args.end(); it++) {
        delete *it;
    }
}