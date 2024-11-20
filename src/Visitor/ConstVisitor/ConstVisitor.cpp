#include <iostream>
#include "Visitor/ConstVisitor/ConstVisitor.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

IVisitorReturn* ConstVisitor::evalBinaryExp_b(const bool& v1, const bool& v2, BinaryOp op) const {
    // eval expression
    bool result;
    switch (op) {
        // Boolean operators
        case EQUALS_OP: result = (v1 == v2); break;
        case NEQUALS_OP: result = (v1 != v2); break;
        default: {
            string msg = "Error: Operacion binaria incompatible para bool";
            throw runtime_error(msg);
        }
    }
    return new VariantReturn(result);
}

IVisitorReturn* ConstVisitor::evalUnaryExp_b(const bool& v, UnaryOp op) const {
    // eval expression
    bool result;
    switch (op) {
        // Boolean operators
        case NOT_OP: result = !v; break;
        default: {
            string msg = "Error: Operacion unaria incompatible para bool";
            throw runtime_error(msg);
        }
    }
    return new VariantReturn(result);
}

ConstVariant ConstVisitor::getValue(IVisitorReturn* ret) const {
    ConstVariant value = dynamic_cast<VariantReturn*>(ret)->value;
    if (ret) delete ret;
    return value;
}

void ConstVisitor::replaceASTNode(Exp*& exp, const ConstVariant& value) {
    delete exp;
    if (holds_alternative<bool>(value)) {
        exp = new IntegerExp(get<bool>(value));
    }
    else if (holds_alternative<int32_t>(value)) {
        exp = new IntegerExp(get<int32_t>(value));
    }
    else if (holds_alternative<int64_t>(value)) {
        exp = new IntegerExp(get<int64_t>(value));
    }
    else if (holds_alternative<uint32_t>(value)) {
        exp = new IntegerExp(get<uint32_t>(value));
    }
    else if (holds_alternative<uint64_t>(value)) {
        exp = new IntegerExp(get<uint64_t>(value));
    }
    else {
        string msg = "Error: No se pudo reemplazar la constante";
        throw runtime_error(msg);
    }
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
    ConstVariant value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(vardec->exp, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(StaticVar* vardec) {
    varEnv.addVariable(vardec->id, {EnvVariable::STATIC_VAR, vardec->type, vardec->mut});
    auto e = vardec->exp->accept(this);
    if (!e) return;
    ConstVariant value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(vardec->exp, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(ConstVar* vardec) {
    varEnv.addVariable(vardec->id, {EnvVariable::CONST_VAR, vardec->type, false});
    fetchingForConst = true;
    lhsUnsigned = (vardec->type == VarType::UINT32_TYPE || vardec->type == VarType::UINT64_TYPE);
    auto e = vardec->exp->accept(this);
    lhsUnsigned = false;
    fetchingForConst = false;
    ConstVariant value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(vardec->exp, value);
        replacingRootExp = false;
    }
    constEnv.addVariable(vardec->id, value);
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
    ConstVariant value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(stm->exp, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(AssignStatement* stm) {
    auto e = stm->rhs->accept(this);
    if (!e) return;
    ConstVariant value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(stm->rhs, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(AdvanceStatement* stm) {
    auto e = stm->rhs->accept(this);
    if (!e) return;
    ConstVariant value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(stm->rhs, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(ReturnStatement* stm) {
    if (!stm->exp) return;
    auto e = stm->exp->accept(this);
    if (!e) return;
    ConstVariant value = getValue(e);
    if (replacingRootExp) {
        replaceASTNode(stm->exp, value);
        replacingRootExp = false;
    }
}

void ConstVisitor::visit(PrintStatement* stm) {
    for (auto it = stm->expList.begin(); it != stm->expList.end(); it++) {
        auto e = (*it)->accept(this);
        if (!e) continue;
        ConstVariant value = getValue(e);
        if (replacingRootExp) {
            replaceASTNode(*it, value);
            replacingRootExp = false;
        }
    }
}

void ConstVisitor::visit(IfStatement* stm) {
    auto e = stm->condition->accept(this);
    if (e) {
        ConstVariant value = getValue(e);
        if (replacingRootExp) {
            replaceASTNode(stm->condition, value);
            replacingRootExp = false;
        }
    }
    stm->ifBody->accept(this);
    if (stm->elseBody) stm->elseBody->accept(this);
}

void ConstVisitor::visit(WhileStatement* stm) {
    auto e = stm->condition->accept(this);
    if (e) {
        ConstVariant value = getValue(e);
        if (replacingRootExp) {
            replaceASTNode(stm->condition, value);
            replacingRootExp = false;
        }
    }
    stm->body->accept(this);
}

void ConstVisitor::visit(ForStatement* stm) {
    auto e = stm->start->accept(this);
    if (!e) return;
    ConstVariant value = getValue(e);
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
    stm->body->accept(this);
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
        if (holds_alternative<int32_t>(v1)) {
            return evalBinaryExp<int32_t>(get<int32_t>(v1), get<int32_t>(v2), exp->op);
        }
        else if (holds_alternative<int64_t>(v1)) {
            return evalBinaryExp<int64_t>(get<int64_t>(v1), get<int64_t>(v2), exp->op);
        }
        else if (holds_alternative<uint32_t>(v1)) {
            return evalBinaryExp<uint32_t>(get<uint32_t>(v1), get<uint32_t>(v2), exp->op);
        }
        else if (holds_alternative<uint64_t>(v1)) {
            return evalBinaryExp<uint64_t>(get<uint64_t>(v1), get<uint64_t>(v2), exp->op);
        }
        else if (holds_alternative<bool>(v1)) {
            return evalBinaryExp_b(get<bool>(v1), get<bool>(v2), exp->op);
        }
    }

    if (e1) delete e1;
    if (e2) delete e2;
    return nullptr;
}

IVisitorReturn* ConstVisitor::visit(UnaryExp* exp) {
    expParent = exp;
    parentType = ExpParentType::UNARY_EXP;
    auto e = exp->exp->accept(this);
    expParent = nullptr;
    parentType = ExpParentType::NONE;

    if (e) {
        auto v = getValue(e);
        if (holds_alternative<int32_t>(v)) {
            return evalUnaryExp<int32_t>(get<int32_t>(v), exp->op);
        }
        else if (holds_alternative<int64_t>(v)) {
            return evalUnaryExp<int64_t>(get<int64_t>(v), exp->op);
        }
        else if (holds_alternative<uint32_t>(v)) {
            return evalUnaryExp<uint32_t>(get<uint32_t>(v), exp->op);
        }
        else if (holds_alternative<uint64_t>(v)) {
            return evalUnaryExp<uint64_t>(get<uint64_t>(v), exp->op);
        }
        else if (holds_alternative<bool>(v)) {
            return evalUnaryExp_b(get<bool>(v), exp->op);
        }
    }
    return nullptr;
}

IVisitorReturn* ConstVisitor::visit(IntegerExp* exp) {
    switch (exp->type) {
        case VarType::INT32_TYPE: return new VariantReturn(get<int32_t>(exp->value)); break;
        case VarType::INT64_TYPE: return new VariantReturn(get<int64_t>(exp->value)); break;
        case VarType::UINT32_TYPE: return new VariantReturn(get<uint32_t>(exp->value)); break;
        case VarType::UINT64_TYPE: return new VariantReturn(get<uint64_t>(exp->value)); break;
        case VarType::BOOL_TYPE: return new VariantReturn(get<bool>(exp->value)); break;
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
    ConstVariant value = constEnv.getVariableValue(exp->name).value();
    // replace id ast node for int ast node
    if (expParent) {
        switch (parentType) {
            case ExpParentType::BINARY_EXP: {
                BinaryExp* bExp = dynamic_cast<BinaryExp*>(expParent);
                replaceBinary(bExp, exp, value);
                break;
            }
            case ExpParentType::FUNCTION_EXP: {
                FunctionExp* fExp = dynamic_cast<FunctionExp*>(expParent);
                replaceFunction(fExp, exp, value);
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
    return new VariantReturn(value);
}

IVisitorReturn* ConstVisitor::visit(FunctionExp* exp) {
    for (auto it = exp->args.begin(); it != exp->args.end(); it++) {
        auto e = (*it)->accept(this);
        if (!e) continue;
        ConstVariant value = getValue(e);
        if (replacingRootExp) {
            replaceASTNode(*it, value);
            replacingRootExp = false;
        }
    }
    return nullptr;
}

void ConstVisitor::replaceBinary(BinaryExp* parent, IdentifierExp* child, const ConstVariant& value) {
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

void ConstVisitor::replaceFunction(FunctionExp* parent, IdentifierExp* child, const ConstVariant& value) {
    for (auto it = parent->args.begin(); it != parent->args.end(); it++) {
        if (*it != child) continue;
        replaceASTNode(*it, value);
        return;
    }
    string msg = "Error: No se pudo reemplazar '" + child->name + "' por un valor constante";
    throw runtime_error(msg);
}