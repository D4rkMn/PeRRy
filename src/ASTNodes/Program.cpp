#include <iostream>
#include "ASTNodes/Program.h"
#include "ASTNodes/Exp.h"
using namespace std;

// Variable Declarations

LetVar::LetVar(bool mut, const string& id, VarType type, Exp* exp)
    : mut(mut), id(id), type(type), exp(exp) {}
LetVar::~LetVar() { delete exp; }

StaticVar::StaticVar(bool mut, const string& id, VarType type, Exp* exp)
    : mut(mut), id(id), type(type), exp(exp) {}
StaticVar::~StaticVar() { delete exp; }

ConstVar::ConstVar(const string& id, VarType type, Exp* exp)
    : id(id), type(type), exp(exp) {}
ConstVar::~ConstVar() { delete exp; }

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
    if (node->getType() == STATICVAR_NODE) {
        throw runtime_error("Error: Body can't have a static variable!");
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
    if (node->getType() == LETVAR_NODE) {
        throw runtime_error("Error: Program can't have a 'let' variable declaration!");
    }
    programList.push_back(node);
}