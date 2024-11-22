#include "R/Utility/FunctionType.h"
#include "R/ASTNodes/Function.h"
using namespace std;

R::FunctionType::FunctionType(VarType type, ParamDecList* params) : returnType(type) {
    if (!params) return;
    for (auto it = params->params.begin(); it != params->params.end(); it++) {
        this->params.push_back(it->type);
    }
}