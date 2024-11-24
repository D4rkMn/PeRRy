#include <iostream>
#include "R/Visitor/TypeVisitor/TypeVisitor.h"
#include "R/Visitor/TypeVisitor/TypeReturn.h"
#include "R/Utility/NumberTester.h"

#include "R/ASTNodes/Program.h"
#include "R/ASTNodes/Function.h"
#include "R/ASTNodes/Stm.h"
#include "R/ASTNodes/Exp.h"
using namespace std;

void R::TypeVisitor::checkTypes(VarType expected, VarType obtained) const {
    if (expected != obtained) {
        throw TypeError(expected, obtained);
    }
}

bool R::TypeVisitor::tryImplicitCast(VarType type, IntegerExp*& exp) const {
    int32_t v = get<int32_t>(exp->value);
    if (type == VarType::INT32_TYPE) {
        return true;
    }
    if (type == VarType::INT64_TYPE) {
        exp->value = int64_t(v);
        exp->type = VarType::INT64_TYPE;
        return true;
    }
    string s = to_string(v);
    if (type == VarType::UINT32_TYPE) {
        bool b = NumberTester::fitsInUInt32(s);
        if (b) {
            exp->value = uint32_t(v);
            exp->type = VarType::UINT32_TYPE;
            return true;
        }
        return false;
    }
    if (type == VarType::UINT64_TYPE) {
        bool b = NumberTester::fitsInUInt64(s);
        if (b) {
            exp->value = uint64_t(v);
            exp->type = VarType::UINT64_TYPE;
            return true;
        }
        return false;
    }
    if (type == VarType::BOOL_TYPE) {
        return false;
    }
    return false;
}

runtime_error R::TypeVisitor::TypeError(VarType expected, VarType obtained) const {
    string msg = "Error: Se esperaba '" + varTypeToString(expected) + "', pero se obtuvo '" + varTypeToString(obtained) + "'";
    return runtime_error(msg);
}

R::VarType R::TypeVisitor::getType(IVisitorReturn* ret) const {
    VarType obtainedType = dynamic_cast<TypeReturn*>(ret)->varType;
    if (ret) delete ret;
    return obtainedType;
}

void R::TypeVisitor::check(Program* program) {
    awaitingReturn = false;
    if (isDebug) cout << "Verificando tipos:\n";
    program->accept(this);
    if (isDebug) cout << "Type checker exitoso\n\n";
}

// Program
void R::TypeVisitor::visit(Program* program) {
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

void R::TypeVisitor::visit(Body* body) {
    varEnv.addLevel();
    for (auto it = body->bodyList.begin(); it != body->bodyList.end(); it++) {
        (*it)->accept(this);
    }
    varEnv.removeLevel();
}

void R::TypeVisitor::visit(LetVar* vardec) {
    if (vardec->type == VarType::UNKNOWN_TYPE) {
        lhsType = vardec->type;
        vardec->type = getType(vardec->exp->accept(this));
        if (vardec->type == VarType::VOID_TYPE) {
            string msg = "Error: Se intentó asignar 'void' a una variable";
            throw runtime_error(msg);
        }
        lhsType = VarType::VOID_TYPE;
        varEnv.addVariable(vardec->id, {EnvVariable::LET_VAR, vardec->type, vardec->mut});
        return;
    }
    if (!vardec->exp) {
        varEnv.addVariable(vardec->id, {EnvVariable::LET_VAR, vardec->type, vardec->mut});
        return;
    }
    lhsType = vardec->type;
    VarType obtainedType = getType(vardec->exp->accept(this));
    lhsType = VarType::VOID_TYPE;
    checkTypes(vardec->type, obtainedType);
    varEnv.addVariable(vardec->id, {EnvVariable::LET_VAR, vardec->type, vardec->mut});
}

void R::TypeVisitor::visit(StaticVar* vardec) {
    lhsType = vardec->type;
    VarType obtainedType = getType(vardec->exp->accept(this));
    lhsType = VarType::VOID_TYPE;
    checkTypes(vardec->type, obtainedType);
    varEnv.addVariable(vardec->id, {EnvVariable::STATIC_VAR, vardec->type, vardec->mut});
}

void R::TypeVisitor::visit(ConstVar* vardec) {
    lhsType = vardec->type;
    VarType obtainedType = getType(vardec->exp->accept(this));
    lhsType = VarType::VOID_TYPE;
    checkTypes(vardec->type, obtainedType);
    varEnv.addVariable(vardec->id, {EnvVariable::CONST_VAR, vardec->type, false});
}

// Function
void R::TypeVisitor::visit(Function* function) {
    FunctionType fType(function->type, function->params);
    functionEnv.addVariable(function->id, fType);
    varEnv.addLevel();
    if (function->params) function->params->accept(this);
    expectedReturnType = function->type;
    obtainedReturnType = VarType::VOID_TYPE;
    function->body->accept(this);
    checkTypes(expectedReturnType, obtainedReturnType);
    expectedReturnType = VarType::UNKNOWN_TYPE;
    varEnv.removeLevel();
    if (function->type == VarType::VOID_TYPE) {
        function->body->bodyList.push_back(new ReturnStatement(nullptr));
    }
}

void R::TypeVisitor::visit(ParamDecList* params) {
    for (auto it = params->params.begin(); it != params->params.end(); it++) {
        it->accept(this);
    }
}

void R::TypeVisitor::visit(ParamDec* param) {
    varEnv.addVariable(param->id, {EnvVariable::LET_VAR, param->type, param->mut});
}

// Stm
void R::TypeVisitor::visit(ExpStatement* stm) {
    isExpStm = true;
    stm->exp->accept(this);
    isExpStm = false;
}

void R::TypeVisitor::visit(AssignStatement* stm) {
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
    lhsType = var.varType;
    VarType rhsType = getType(stm->rhs->accept(this));
    lhsType = VarType::VOID_TYPE;
    checkTypes(var.varType, rhsType);
}

void R::TypeVisitor::visit(AdvanceStatement* stm) {
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
    lhsType = var.varType;
    VarType rhsType = getType(stm->rhs->accept(this));
    lhsType = VarType::VOID_TYPE;
    checkTypes(var.varType, rhsType);
}

void R::TypeVisitor::visit(ReturnStatement* stm) {
    obtainedReturnType = VarType::VOID_TYPE;
    if (stm->exp) {
        awaitingReturn = true;
        obtainedReturnType = getType(stm->exp->accept(this));
        awaitingReturn = false;
    }
    checkTypes(expectedReturnType, obtainedReturnType);
}

void R::TypeVisitor::visit(PrintStatement* stm) {
    lhsType = VarType::UNKNOWN_TYPE;
    for (auto it = stm->expList.begin(); it != stm->expList.end(); it++) {
        (*it)->accept(this);
    }
    lhsType = VarType::VOID_TYPE;
}

void R::TypeVisitor::visit(IfStatement* stm) {
    stm->ifBody->accept(this);
    if (stm->elseBody) stm->elseBody->accept(this);
}

void R::TypeVisitor::visit(WhileStatement* stm) {
    stm->body->accept(this);
}

void R::TypeVisitor::visit(ForStatement* stm) {
    varEnv.addLevel();
    varEnv.addVariable(stm->id, EnvVariable());
    stm->body->accept(this);
    varEnv.removeLevel();
}

void R::TypeVisitor::visit(UnsafeStatement* stm) {
    varEnv.addLevel();
    varEnv.addVariable("unsafe", EnvVariable());
    stm->body->accept(this);
    varEnv.removeLevel();
}

void R::TypeVisitor::visit(ScopeStatement* stm) {
    stm->body->accept(this);
}

// Exp
R::IVisitorReturn* R::TypeVisitor::visit(BinaryExp* exp) {
    if (
        exp->op == LESS_OP || exp->op == LESS_EQ_OP ||
        exp->op == GREATER_OP || exp->op == GREATER_EQ_OP ||
        exp->op == EQUALS_OP || exp->op == NEQUALS_OP
    ) {
        checkingComparison = true;
    }
    VarType type1 = getType(exp->left->accept(this));
    VarType type2 = getType(exp->right->accept(this));
    checkingComparison = false;
    checkTypes(type1, type2);
    // if comparison (but not equality) expression
    if (
        exp->op == LESS_OP || exp->op == LESS_EQ_OP ||
        exp->op == GREATER_OP || exp->op == GREATER_EQ_OP
    ) {
        if (type1 == VarType::BOOL_TYPE || type2 == VarType::BOOL_TYPE) {
            string msg = "Error: Se intento realizar una operación de comparación entre bools";
            throw runtime_error(msg);
        }
        return new TypeReturn(VarType::BOOL_TYPE);
    }
    // if arithmetic binary expression
    else if (exp->op != EQUALS_OP && exp->op != NEQUALS_OP) {
        if (type1 == VarType::BOOL_TYPE || type2 == VarType::BOOL_TYPE) {
            string msg = "Error: Se intento realizar una operación aritmética entre bools";
            throw runtime_error(msg);
        }
        return new TypeReturn(type1);
    }
    // if equality comparison
    else {
        return new TypeReturn(VarType::BOOL_TYPE);
    }
}

R::IVisitorReturn* R::TypeVisitor::visit(UnaryExp* exp) {
    VarType _type;
    if (awaitingReturn) {
        _type = expectedReturnType;
    }
    else {
        _type = lhsType;
    }
    // if trying to do a negative literal to an unsigned value,
    // it may not be able to determine at runtime if this is valid,
    // so this will just throw error in this case
    if (exp->op == NEG_OP && (_type == VarType::UINT32_TYPE || _type == VarType::UINT64_TYPE)) {
        string msg = "Error: Se intento asignar un valor negativo a una variable de tipo '" + varTypeToString(_type) + "'";
        throw runtime_error(msg);
    }
    VarType type = getType(exp->exp->accept(this));
    if (exp->op == NEG_OP && type == VarType::BOOL_TYPE) {
        string msg = "Error: Se intento realizar una operación aritmética a un bool";
        throw runtime_error(msg);
    }
    if (exp->op == NOT_OP && type != VarType::BOOL_TYPE) {
        string msg = "Error: Se intento realizar una lógica aritmética a un entero";
        throw runtime_error(msg);    
    }
    return new TypeReturn(type);
}

R::IVisitorReturn* R::TypeVisitor::visit(IntegerExp* exp) {
    if (checkingComparison) {
        exp->isImplicit = false;
        return new TypeReturn(exp->type);
    }
    if (lhsType == VarType::UNKNOWN_TYPE) {
        exp->isImplicit = false;
        return new TypeReturn(exp->type);
    }
    if (exp->isImplicit) {
        bool castable;
        if (awaitingReturn) {
            castable = tryImplicitCast(expectedReturnType, exp);
            if (!castable) {
                checkTypes(expectedReturnType, exp->type);
            }
        }
        else if (!isExpStm) {
            castable = tryImplicitCast(lhsType, exp);
            if (!castable) {
                checkTypes(lhsType, exp->type);
            }
        }
    }
    return new TypeReturn(exp->type);
}

R::IVisitorReturn* R::TypeVisitor::visit(IdentifierExp* exp) {
    auto option = varEnv.getVariableValue(exp->name);
    if (!option.has_value()) {
        string msg = "Error: La variable '" + exp->name + "' no ha sido declarada en este scope";
        throw runtime_error(msg);
    }
    EnvVariable var = option.value();
    return new TypeReturn(var.varType);
}

R::IVisitorReturn* R::TypeVisitor::visit(FunctionExp* exp) {
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
    auto it1 = fType.params.begin();
    auto it2 = exp->args.begin();
    for (; it1 != fType.params.end(); ) {
        lhsType = *it1;
        auto type = getType((*it2)->accept(this));
        lhsType = VarType::VOID_TYPE;
        checkTypes(*it1, type);
        it1++; it2++;
    }
    return new TypeReturn(fType.returnType);
}