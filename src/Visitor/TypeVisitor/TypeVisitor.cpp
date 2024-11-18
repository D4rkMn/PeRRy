#include <iostream>
#include "Visitor/TypeVisitor/TypeVisitor.h"
#include "Visitor/TypeVisitor/TypeReturn.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

// TODO: make i32 convertible to i64 
runtime_error TypeVisitor::TypeError(VarType expected, VarType obtained) {
    string msg = "Error: Se esperaba '" + varTypeToString(expected) + "', pero se obtuvo '" + varTypeToString(obtained) + "'";
    return runtime_error(msg);
}

VarType TypeVisitor::getType(IVisitorReturn* ret) const {
    VarType obtainedType = dynamic_cast<TypeReturn*>(ret)->varType;
    if (ret) delete ret;
    return obtainedType;
}

void TypeVisitor::check(Program* program) {
    cout << "Verificando tipos:\n";
    program->accept(this);
    cout << "Type checker exitoso\n\n";
}

// Program
void TypeVisitor::visit(Program* program) {
    varEnv.addLevel();
    functionEnv.addLevel();
    for (auto it = program->programList.begin(); it != program->programList.end(); it++) {
        (*it)->accept(this);
    }
    auto option = functionEnv.getVariableValue("main");
    if (!option.has_value()) {
        string msg = "Error: No se ha definido la función 'main'";
        throw runtime_error(msg);
    }
    if (option.value().params.size() != 0) {
        string msg = "Error: Se esperaban 0 parámetros para la función 'main'";
        throw runtime_error(msg);
    }
    if (option.value().returnType != VarType::VOID_TYPE) {
        string msg = "Error: Se esperaba tipo de retorno 'void' para la función 'main'";
        throw runtime_error(msg);
    }
    functionEnv.removeLevel();
    varEnv.removeLevel();
}

void TypeVisitor::visit(Body* body) {
    varEnv.addLevel();
    for (auto it = body->bodyList.begin(); it != body->bodyList.end(); it++) {
        (*it)->accept(this);
    }
    varEnv.removeLevel();
}

void TypeVisitor::visit(LetVar* vardec) {
    if (vardec->type == VarType::UNKNOWN_TYPE) {
        vardec->type = getType(vardec->exp->accept(this));
        varEnv.addVariable(vardec->id, {EnvVariable::LET_VAR, vardec->type, vardec->mut});
        return;
    }
    if (!vardec->exp) {
        varEnv.addVariable(vardec->id, {EnvVariable::LET_VAR, vardec->type, vardec->mut});
        return;
    }
    VarType obtainedType = getType(vardec->exp->accept(this));
    if (obtainedType != vardec->type) {
        throw TypeError(vardec->type, obtainedType);
    }
    varEnv.addVariable(vardec->id, {EnvVariable::LET_VAR, vardec->type, vardec->mut});
}

void TypeVisitor::visit(StaticVar* vardec) {
    VarType obtainedType = getType(vardec->exp->accept(this));
    if (obtainedType != vardec->type) {
        throw TypeError(vardec->type, obtainedType);
    }
    varEnv.addVariable(vardec->id, {EnvVariable::STATIC_VAR, vardec->type, vardec->mut});
}

void TypeVisitor::visit(ConstVar* vardec) {
    VarType obtainedType = getType(vardec->exp->accept(this));
    if (obtainedType != vardec->type) {
        throw TypeError(vardec->type, obtainedType);
    }
    varEnv.addVariable(vardec->id, {EnvVariable::CONST_VAR, vardec->type, false});
}

// Function
void TypeVisitor::visit(Function* function) {
    FunctionType fType(function->type, function->params);
    functionEnv.addVariable(function->id, fType);
    varEnv.addLevel();
    if (function->params) function->params->accept(this);
    expectedReturnType = function->type;
    function->body->accept(this);
    varEnv.removeLevel();
}

void TypeVisitor::visit(ParamDecList* params) {
    for (auto it = params->params.begin(); it != params->params.end(); it++) {
        it->accept(this);
    }
}

void TypeVisitor::visit(ParamDec* param) {
    varEnv.addVariable(param->id, {EnvVariable::LET_VAR, param->type, param->mut});
}

// Stm
void TypeVisitor::visit(ExpStatement* stm) {
    stm->exp->accept(this);
}

void TypeVisitor::visit(AssignStatement* stm) {
    auto option = varEnv.getVariableValue(stm->id);
    // if var not declared
    if (!option.has_value()) {
        string msg = "Error: '" + stm->id + "' ha sido declarada como const en este scope";
        throw runtime_error(msg);
    }
    // if const
    EnvVariable var = option.value();
    if (var.declType == EnvVariable::CONST_VAR) {
        string msg = "Error: '" + stm->id + "' ha sido declarada como const en este scope";
        throw runtime_error(msg);
    }
    // if non mut
    if (!var.mut) {
        string msg = "Error: '" + stm->id + "' ha sido declarada como inmutable en este scope";
        throw runtime_error(msg);
    }
    // if var is static, check for unsafe scope
    bool isUnsafe = varEnv.checkVariableExists("unsafe");
    if (var.declType == EnvVariable::STATIC_VAR && !isUnsafe) {
        string msg = "Error: La variable estática '" + stm->id + "' no puede ser modificada en un ambiente no marcado como 'unsafe'";
        throw runtime_error(msg);   
    }
    // eval rhs
    VarType rhsType = getType(stm->rhs->accept(this));
    if (var.varType != rhsType) {
        throw TypeError(var.varType, rhsType);
    }
}

void TypeVisitor::visit(AdvanceStatement* stm) {
    auto option = varEnv.getVariableValue(stm->id);
    // if var not declared
    if (!option.has_value()) {
        string msg = "Error: '" + stm->id + "' ha sido declarada como const en este scope";
        throw runtime_error(msg);
    }
    // if const
    EnvVariable var = option.value();
    if (var.declType == EnvVariable::CONST_VAR) {
        string msg = "Error: '" + stm->id + "' ha sido declarada como const en este scope";
        throw runtime_error(msg);
    }
    // if non mut
    if (!var.mut) {
        string msg = "Error: '" + stm->id + "' ha sido declarada como inmutable en este scope";
        throw runtime_error(msg);
    }
    // eval rhs
    VarType rhsType = getType(stm->rhs->accept(this));
    if (var.varType != rhsType) {
        throw TypeError(var.varType, rhsType);
    }
}

void TypeVisitor::visit(ReturnStatement* stm) {
    VarType obtainedReturnType = VarType::VOID_TYPE;
    if (stm->exp) {
        obtainedReturnType = getType(stm->exp->accept(this));
    }
    if (obtainedReturnType != expectedReturnType) {
        throw TypeError(expectedReturnType, obtainedReturnType);
    }
}

void TypeVisitor::visit(PrintStatement* stm) {
    // nothing to check
}

void TypeVisitor::visit(IfStatement* stm) {
    stm->ifBody->accept(this);
    if (stm->elseBody) stm->elseBody->accept(this);
}

void TypeVisitor::visit(ForStatement* stm) {
    varEnv.addLevel();
    varEnv.addVariable(stm->id, EnvVariable());
    stm->body->accept(this);
    varEnv.removeLevel();
}

void TypeVisitor::visit(UnsafeStatement* stm) {
    varEnv.addLevel();
    varEnv.addVariable("unsafe", EnvVariable());
    stm->body->accept(this);
    varEnv.removeLevel();
}

void TypeVisitor::visit(ScopeStatement* stm) {
    stm->body->accept(this);
}

// Exp
IVisitorReturn* TypeVisitor::visit(BinaryExp* exp) {
    VarType type1 = getType(exp->left->accept(this));
    VarType type2 = getType(exp->right->accept(this));
    if (type1 != type2) {
        string msg = "Error: Los tipos '" + varTypeToString(type1) + "' y '" + varTypeToString(type2) + "' no coinciden";
        throw runtime_error(msg);
    }
    return new TypeReturn(type1);
}

IVisitorReturn* TypeVisitor::visit(IntegerExp* exp) {
    return new TypeReturn(exp->type);
}

IVisitorReturn* TypeVisitor::visit(IdentifierExp* exp) {
    auto option = varEnv.getVariableValue(exp->name);
    if (!option.has_value()) {
        string msg = "Error: La variable '" + exp->name + "' no ha sido declarada en este scope";
        throw runtime_error(msg);
    }
    EnvVariable var = option.value();
    return new TypeReturn(var.varType);
}

IVisitorReturn* TypeVisitor::visit(FunctionExp* exp) {
    auto option = functionEnv.getVariableValue(exp->name);
    if (!option.has_value()) {
        string msg = "Error: La función '" + exp->name + "' no ha sido declarada en este scope";
        throw runtime_error(msg);
    }
    FunctionType fType = option.value();
    if (exp->args.size() != fType.params.size()) {
        string msg = "Error: La llamada a la función '" + exp->name + "' no recibió la cantidad correcta de parámetros";
        throw runtime_error(msg);
    }
    std::list<VarType> expTypes;
    for (auto it = exp->args.begin(); it != exp->args.end(); it++) {
        auto type = getType((*it)->accept(this));
        expTypes.push_back(type);
    }
    if (fType.params != expTypes) {
        string msg = "Error: La llamada a la función '" + exp->name +"' recibió parámetros de tipos incorrectos";
        throw runtime_error(msg);
    }
    return new TypeReturn(fType.returnType);
}