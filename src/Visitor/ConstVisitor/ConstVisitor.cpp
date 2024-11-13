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

void ConstVisitor::replace(Program* program) {
    cout << "Reemplazando constantes:\n";
    program->accept(this);
    cout << "Const replacer exitoso\n\n";
}

// Program
void ConstVisitor::visit(Program* program) {
    varEnv.addLevel();
    constEnv.addLevel();
    for (auto it = program->programList.begin(); it != program->programList.end(); it++) {
        (*it)->accept(this);
    }
    constEnv.removeLevel();
    varEnv.removeLevel();
}

void ConstVisitor::visit(Body* body) {
    varEnv.addLevel();
    constEnv.addLevel();
    for (auto it = body->bodyList.begin(); it != body->bodyList.end(); it++) {
        (*it)->accept(this);
    }
    constEnv.removeLevel();
    varEnv.removeLevel();
}

void ConstVisitor::visit(LetVar* vardec) {
    varEnv.addVariable(vardec->id, {EnvVariable::LET_VAR, vardec->type, vardec->mut});
    if (vardec->exp) getValue(vardec->exp->accept(this));
}

void ConstVisitor::visit(StaticVar* vardec) {
    varEnv.addVariable(vardec->id, {EnvVariable::STATIC_VAR, vardec->type, vardec->mut});
    getValue(vardec->exp->accept(this));
}

void ConstVisitor::visit(ConstVar* vardec) {
    varEnv.addVariable(vardec->id, {EnvVariable::CONST_VAR, vardec->type, false});
    fetchingForConst = true;
    long long value = getValue(vardec->exp->accept(this));
    fetchingForConst = false;
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
}

// Function
void ConstVisitor::visit(Function* function) {
    function->body->accept(this);
}

void ConstVisitor::visit(ParamDecList* params) {
    
}

void ConstVisitor::visit(ParamDec* param) {
    
}

// Stm
void ConstVisitor::visit(ExpStatement* stm) {
    
}

void ConstVisitor::visit(AssignStatement* stm) {
    
}

void ConstVisitor::visit(AdvanceStatement* stm) {
    
}

void ConstVisitor::visit(ReturnStatement* stm) {
    
}

void ConstVisitor::visit(PrintStatement* stm) {
    
}

void ConstVisitor::visit(IfStatement* stm) {
    
}

void ConstVisitor::visit(ForStatement* stm) {
    
}

void ConstVisitor::visit(UnsafeStatement* stm) {
    
}

void ConstVisitor::visit(ScopeStatement* stm) {

}

// Exp
IVisitorReturn* ConstVisitor::visit(BinaryExp* exp) {
    // visit children
    expParent = exp;
    parentType = ExpParentType::BINARY_EXP;
    auto v1 = getValue(exp->left->accept(this));
    expParent = exp;
    parentType = ExpParentType::BINARY_EXP;
    auto v2 = getValue(exp->right->accept(this));
    expParent = nullptr;
    parentType = ExpParentType::NONE;
    // eval expression
    long long result;
    switch (exp->op) {
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
        return new LLongReturn(llongValue);
    }
    if (option.declType == EnvVariable::CONST_VAR) {
        IEnvConst* value = constEnv.getVariableValue(exp->name).value();
        long long llongValue = envConstToLLong(value);
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
        return new LLongReturn(llongValue);
    }
    // TODO: check this
    return nullptr;
}

IVisitorReturn* ConstVisitor::visit(FunctionExp* exp) {

}

void ConstVisitor::replaceBinary(BinaryExp* parent, IdentifierExp* child, long long value) {
    if (parent->left && parent->left == child) {
        parent->left = new IntegerExp(value);
        delete child;
        return;
    }
    if (parent->right && parent->right == child) {
        parent->right = new IntegerExp(value);
        delete child;
        return;
    }
    string msg = "Error: No se pudo reemplazar '" + child->name + "' por un valor constante";
    throw runtime_error(msg);
}

void ConstVisitor::replaceFunction(FunctionExp* parent, IdentifierExp* child, long long value) {

}