#include <iostream>
#include "ASTNodes/Program.h"
#include "ASTNodes/Exp.h"
using namespace std;

// VarDec

VarDec::VarDec(bool mut, const string& id, VarType type, Exp* exp)
    : mut(mut), id(id), type(type), exp(exp) {}
VarDec::~VarDec() { delete exp; }

// Body

Body::~Body() {
    for (auto it = bodyList.begin(); it != bodyList.end(); it++) {
        delete *it;
    }
}

void Body::add(ISharedASTNode* node) {
    if (node->getType() == FUNCTION_NODE) {
        throw runtime_error("Error: Body can't have a function!");
    }
    bodyList.push_back(node);
}

// Program

Program::~Program() {
    for (auto it = programList.begin(); it != programList.end(); it++) {
        delete *it;
    }
}

void Program::add(ISharedASTNode* node) {
    if (node->getType() == STM_NODE) {
        throw runtime_error("Error: Program can't have a statement!");
    }
    programList.push_back(node);
}