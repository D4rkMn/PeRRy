#include "ASTNodes/Function.h"
#include "ASTNodes/Program.h"
using namespace std;

// ParamDec

ParamDec::ParamDec(VarType type, const string& id) : type(type), id(id) {}

// ParamDecList

// Function

Function::Function(const string& id, ParamDecList* params, VarType type, Body* body)
    : id(id), params(params), type(type), body(body) {}

Function::~Function() {
    if (params) delete params;
    delete body;
}