#include "R/ASTNodes/Function.h"
#include "R/ASTNodes/Program.h"
using namespace std;

// ParamDec

R::ParamDec::ParamDec(VarType type, const string& id, bool mut) : type(type), id(id), mut(mut) {}

// ParamDecList

// Function

R::Function::Function(const string& id, ParamDecList* params, VarType type, Body* body)
    : id(id), params(params), type(type), body(body) {}

R::Function::~Function() {
    if (params) delete params;
    delete body;
}