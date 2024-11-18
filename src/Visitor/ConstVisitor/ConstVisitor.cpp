#include <iostream>
#include "Visitor/ConstVisitor/ConstVisitor.h"
#include "Visitor/ConstVisitor/Int32EnvConst.h"
#include "Visitor/ConstVisitor/Int64EnvConst.h"
#include "Visitor/ConstVisitor/LLongReturn.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

long long ConstVisitor::getValue(IVisitorReturn* ret) const {
    long long value = dynamic_cast<LLongReturn*>(ret)->value;
    if (ret) delete ret;
    return value;
}

void ConstVisitor::replaceASTNode(Exp*& exp, long long value) {
    delete exp;
    exp = new IntegerExp(value);
}

long long ConstVisitor::envConstToLLong(IEnvConst* envConst) const {
    switch (envConst->getType()) {
        case VarType::INT32_TYPE: {
            auto _envconst = dynamic_cast<Int32EnvConst*>(envConst);
            return _envconst->value;
            break;
        }
        case VarType::INT64_TYPE: {
            auto _envconst = dynamic_cast<Int64EnvConst*>(envConst);
            return _envconst->value;
            break;
        }
        default: {
            string msg = "Error: No se pudo obtener el valor de la constante";
            throw runtime_error(msg);
        }
    }
}

IVisitorReturn* ConstVisitor::evalBinaryExp(long long v1, long long v2, BinaryOp op) const {
    // eval expression
    long long result;
    switch (op) {
        // Arithmetic operators
        case PLUS_OP: result = v1 + v2; break;
        case MINUS_OP: result = v1 - v2; break;
        case MUL_OP: result = v1 * v2; break;
        case DIV_OP: result = v1 / v2; break;
        // Boolean operators
        case LESS_OP: result = (v1 < v2); break;
        case LESS_EQ_OP: result = (v1 <= v2); break;
        case EQUALS_OP: result = (v1 == v2); break;
        case GREATER_OP: result = (v1 > v2); break;
        case GREATER_EQ_OP: result = (v1 >= v2); break;
        case NEQUALS_OP: result = (v1 != v2); break;
        default: {
            string msg = "Error: Operacion binaria desconocida";
            throw runtime_error(msg);
        }
    }
    return new LLongReturn(result);
}

void ConstVisitor::replace(Program* program) {
    cout << "Reemplazando constantes:\n";
    program->accept(this);
    cout << "Const replacer exitoso\n\n";
}

// Program
void ConstVisitor::visit(Program* program) {
    varEnv.addLevel();
    constEnv.addLevel();
    for (auto it = program->programList.begin(); it != program->programList.end();) {
        (*it)->accept(this);
        if (deleteConstDec) {
            it = program->programList.erase(it);
            deleteConstDec = false;
        }
        else {
            it++;
        }
    }
    constEnv.removeLevel();
    varEnv.removeLevel();
}

void ConstVisitor::visit(Body* body) {
    varEnv.addLevel();
    constEnv.addLevel();
    for (auto it = body->bodyList.begin(); it != body->bodyList.end();) {
        (*it)->accept(this);
        if (deleteConstDec) {
            it = body->bodyList.erase(it);
            deleteConstDec = false;
        }
        else {
            it++;
        }
    }
    constEnv.removeLevel();
    varEnv.removeLevel();
}

void ConstVisitor::visit(LetVar* vardec) {
    varEnv.addVariable(vardec->id, {EnvVariable::LET_VAR, vardec->type, vardec->mut});
    if (!vardec->exp) {
        return;
    }
    auto e = vardec->exp->accept(this);
    if (!e) return;
    long long value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(vardec->exp, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(StaticVar* vardec) {
    varEnv.addVariable(vardec->id, {EnvVariable::STATIC_VAR, vardec->type, vardec->mut});
    auto e = vardec->exp->accept(this);
    if (!e) return;
    long long value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(vardec->exp, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(ConstVar* vardec) {
    varEnv.addVariable(vardec->id, {EnvVariable::CONST_VAR, vardec->type, false});
    fetchingForConst = true;
    auto e = vardec->exp->accept(this);
    fetchingForConst = false;
    long long value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(vardec->exp, value);
        replacingRootExp = false;
    }
    IEnvConst* constType = nullptr;
    switch (vardec->type) {
        case VarType::INT32_TYPE: constType = new Int32EnvConst(value); break;
        case VarType::INT64_TYPE: constType = new Int64EnvConst(value); break;
        default: {
            string msg = "Error: Tipo desconocido - '" + varTypeToString(vardec->type) + "'";
            throw runtime_error(msg);
        }
    }
    constEnv.addVariable(vardec->id, constType);
    deleteConstDec = true;
}

// Function
void ConstVisitor::visit(Function* function) {
    varEnv.addLevel();
    constEnv.addLevel();
    if (function->params) function->params->accept(this);
    function->body->accept(this);
    constEnv.removeLevel();
    varEnv.removeLevel();
}

void ConstVisitor::visit(ParamDecList* params) {
    for (auto it = params->params.begin(); it != params->params.end(); it++) {
        it->accept(this);
    }
}

void ConstVisitor::visit(ParamDec* param) {
    varEnv.addVariable(param->id, {EnvVariable::LET_VAR, param->type, param->mut});
}

// Stm
void ConstVisitor::visit(ExpStatement* stm) {
    auto e = stm->exp->accept(this);
    if (!e) return;
    long long value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(stm->exp, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(AssignStatement* stm) {
    auto e = stm->rhs->accept(this);
    if (!e) return;
    long long value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(stm->rhs, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(AdvanceStatement* stm) {
    auto e = stm->rhs->accept(this);
    if (!e) return;
    long long value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(stm->rhs, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(ReturnStatement* stm) {
    if (!stm->exp) return;
    auto e = stm->exp->accept(this);
    if (!e) return;
    long long value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(stm->exp, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(PrintStatement* stm) {
    for (auto it = stm->expList.begin(); it != stm->expList.end(); it++) {
        auto e = (*it)->accept(this);
        if (!e) continue;
        long long value = getValue(e);
        if (replacingRootExp) {
            replaceASTNode(*it, value);
            replacingRootExp = false;
        }
    }
}

void ConstVisitor::visit(IfStatement* stm) {
    auto e = stm->condition->accept(this);
    if (e) {
        long long value = getValue(e);
        if (replacingRootExp) {
            replaceASTNode(stm->condition, value);
            replacingRootExp = false;
        }
    }
    stm->ifBody->accept(this);
    if (stm->elseBody) stm->elseBody->accept(this);
}

void ConstVisitor::visit(ForStatement* stm) {
    auto e = stm->start->accept(this);
    if (!e) return;
    long long value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(stm->start, value);
        replacingRootExp = false;
    }
    e = stm->end->accept(this);
    if (!e) return;
    value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(stm->end, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(UnsafeStatement* stm) {
    stm->body->accept(this);
}

void ConstVisitor::visit(ScopeStatement* stm) {
    stm->body->accept(this);
}

// Exp
IVisitorReturn* ConstVisitor::visit(BinaryExp* exp) {
    // visit children
    expParent = exp;
    parentType = ExpParentType::BINARY_EXP;
    auto e1 = exp->left->accept(this);
    
    expParent = exp;
    parentType = ExpParentType::BINARY_EXP;
    auto e2 = exp->right->accept(this);
    
    expParent = nullptr;
    parentType = ExpParentType::NONE;
    
    if (e1 && e2) {
        auto v1 = getValue(e1);
        auto v2 = getValue(e2);
        return evalBinaryExp(v1, v2, exp->op);   
    }

    if (e1) delete e1;
    if (e2) delete e2;
    return nullptr;
}

IVisitorReturn* ConstVisitor::visit(IntegerExp* exp) {
    switch (exp->type) {
        case VarType::INT32_TYPE: return new LLongReturn(exp->value); break;
        case VarType::INT64_TYPE: return new LLongReturn(exp->value); break;
        default: {
            string msg = "Error: Tipo desconocido - '" + varTypeToString(exp->type) + "'";
            throw runtime_error(msg);
        }
    }
}

IVisitorReturn* ConstVisitor::visit(IdentifierExp* exp) {
    EnvVariable option = varEnv.getVariableValue(exp->name).value();
    if (fetchingForConst) {
        // const var inits have to be computable at compile time
        if (option.declType != EnvVariable::CONST_VAR) {
            string msg = "Error: La variable no constante '" + exp->name + "' se intentó asignar a una constante";
            throw runtime_error(msg);
        }
    }
    if (option.declType != EnvVariable::CONST_VAR) {
        return nullptr;
    }
    // get init value
    IEnvConst* value = constEnv.getVariableValue(exp->name).value();
    long long llongValue = envConstToLLong(value);
    // replace id ast node for int ast node
    if (expParent) {
        switch (parentType) {
            case ExpParentType::BINARY_EXP: {
                BinaryExp* bExp = dynamic_cast<BinaryExp*>(expParent);
                replaceBinary(bExp, exp, llongValue);
                break;
            }
            case ExpParentType::FUNCTION_EXP: {
                FunctionExp* fExp = dynamic_cast<FunctionExp*>(expParent);
                replaceFunction(fExp, exp, llongValue);
                break;
            }
            default: {
                string msg = "Error: No se pudo reemplazar '" + exp->name + "' por un valor constante";
                throw runtime_error(msg);
            }
        }
    }
    // if IdExp is root of the ast, mark as replacing root
    else {
        replacingRootExp = true;
    }
    return new LLongReturn(llongValue);
}

IVisitorReturn* ConstVisitor::visit(FunctionExp* exp) {
    for (auto it = exp->args.begin(); it != exp->args.end(); it++) {
        auto e = (*it)->accept(this);
        if (!e) continue;
        long long value = getValue(e);
        if (replacingRootExp) {
            replaceASTNode(*it, value);
            replacingRootExp = false;
        }
    }
    return nullptr;
}

void ConstVisitor::replaceBinary(BinaryExp* parent, IdentifierExp* child, long long value) {
    if (parent->left && parent->left == child) {
        replaceASTNode(parent->left, value);
        return;
    }
    if (parent->right && parent->right == child) {
        replaceASTNode(parent->right, value);
        return;
    }
    string msg = "Error: No se pudo reemplazar '" + child->name + "' por un valor constante";
    throw runtime_error(msg);
}

void ConstVisitor::replaceFunction(FunctionExp* parent, IdentifierExp* child, long long value) {
    for (auto it = parent->args.begin(); it != parent->args.end(); it++) {
        if (*it != child) continue;
        replaceASTNode(*it, value);
        return;
    }
    string msg = "Error: No se pudo reemplazar '" + child->name + "' por un valor constante";
    throw runtime_error(msg);
}