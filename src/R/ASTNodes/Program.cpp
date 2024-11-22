#include <iostream>
#include "R/ASTNodes/Program.h"
#include "R/ASTNodes/Exp.h"
using namespace std;

// Variable Declarations

R::LetVar::LetVar(bool mut, const string& id, VarType type, Exp* exp)
    : mut(mut), id(id), type(type), exp(exp) {}
R::LetVar::~LetVar() { delete exp; }

R::StaticVar::StaticVar(bool mut, const string& id, VarType type, Exp* exp)
    : mut(mut), id(id), type(type), exp(exp) {}
R::StaticVar::~StaticVar() { delete exp; }

R::ConstVar::ConstVar(const string& id, VarType type, Exp* exp)
    : id(id), type(type), exp(exp) {}
R::ConstVar::~ConstVar() { delete exp; }

// Body

R::Body::~Body() {
    for (auto it = bodyList.begin(); it != bodyList.end(); it++) {
        delete *it;
    }
}

void R::Body::add(ISharedASTNode* node) {
    if (node->getType() == FUNCTION_NODE) {
        throw runtime_error("Error: Body can't have a function!");
    }
    if (node->getType() == STATICVAR_NODE) {
        throw runtime_error("Error: Body can't have a static variable!");
    }
    bodyList.push_back(node);
}

// Program

R::Program::~Program() {
    for (auto it = programList.begin(); it != programList.end(); it++) {
        delete *it;
    }
}

void R::Program::add(ISharedASTNode* node) {
    if (node->getType() == STM_NODE) {
        throw runtime_error("Error: Program can't have a statement!");
    }
    if (node->getType() == LETVAR_NODE) {
        throw runtime_error("Error: Program can't have a 'let' variable declaration!");
    }
    programList.push_back(node);
}