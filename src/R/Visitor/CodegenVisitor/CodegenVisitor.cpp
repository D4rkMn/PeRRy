#include <iostream>
#include "R/Visitor/CodegenVisitor/CodegenVisitor.h"

#include "R/ASTNodes/Program.h"
#include "R/ASTNodes/Function.h"
#include "R/ASTNodes/Stm.h"
#include "R/ASTNodes/Exp.h"
using namespace std;

// TODO: make it so that type checker enforces return value for non void

string R::CodegenVisitor::nextLabel() {
    string result = "L" + to_string(labels++);
    return result;
}

void R::CodegenVisitor::output(std::ofstream& output) {
    output << out.str() << "\n";
}

void R::CodegenVisitor::generate(Program* program) {
    if (isDebug) cout << "Generando código:\n\n";
    program->accept(this);
    if (isDebug) {
        cout << out.str() << "\n";
        cout << "Codegen exitoso\n\n";
    }
}

// Program

void R::CodegenVisitor::visit(Program* program) {
    env.addLevel();
    for (auto it = program->programList.begin(); it != program->programList.end(); it++) {
        // global var declarations
        if ((*it)->getType() == ASTNodeType::STATICVAR_NODE) {
            (*it)->accept(this);
        }
    }
    out << "MSTp\n"; // mark before main (MSTp for calling procedure main)
    out << "CUP main\n"; // call main
    out << "STP\n"; // stop program
    for (auto it = program->programList.begin(); it != program->programList.end(); it++) {
        // define functions
        if ((*it)->getType() == ASTNodeType::FUNCTION_NODE) {
            (*it)->accept(this);
        }
    }
    env.removeLevel();
}

void R::CodegenVisitor::visit(Body* body) {
    // MST is for mark stack for entering scope
    out << "MST\n";
    env.addLevel();
    for (auto it = body->bodyList.begin(); it != body->bodyList.end(); it++) {
        (*it)->accept(this);
    }
    env.removeLevel();
    // RET is for exiting scope
    out << "RET\n";
}

void R::CodegenVisitor::visit(LetVar* vardec) {
    env.addVariable(vardec->id, vardec->type);
    if (!vardec->exp) return;
    out << "LDA " << vardec->id << "\n";
    if (vardec->type == VarType::UINT32_TYPE || vardec->type == VarType::UINT64_TYPE) {
        isUnsigned = true;
    } 
    vardec->exp->accept(this);
    isUnsigned = false;
    out << "STOc" << "\n";
}

void R::CodegenVisitor::visit(StaticVar* vardec) {
    env.addVariable(vardec->id, vardec->type);
    out << "LDA " << vardec->id << "\n";
    if (vardec->type == VarType::UINT32_TYPE || vardec->type == VarType::UINT64_TYPE) {
        isUnsigned = true;
    } 
    vardec->exp->accept(this);
    isUnsigned = false;
    out << "STOc" << "\n";
}

void R::CodegenVisitor::visit(ConstVar* vardec) {
    // nothing to do
}

// Function

void R::CodegenVisitor::visit(Function* function) {
    out << "ENT " << function->id << "\n";
    env.addLevel();
    function->body->accept(this);
    env.removeLevel();
    // RETn is for return nothing
    out << "RETn\n";
}

void R::CodegenVisitor::visit(ParamDecList* params) {
    for (auto it = params->params.begin(); it != params->params.end(); it++) {
        it->accept(this);
    }
}

void R::CodegenVisitor::visit(ParamDec* param) {
    env.addVariable(param->id, param->type);
}

// Stm

void R::CodegenVisitor::visit(ExpStatement* stm) {
    stm->exp->accept(this);
    out << "POP\n";
}

void R::CodegenVisitor::visit(AssignStatement* stm) {
    VarType type = env.getVariableValue(stm->id).value();
    out << "LDA " << stm->id << "\n";
    if (type == VarType::UINT32_TYPE || type == VarType::UINT64_TYPE) {
        isUnsigned = true;
    }
    stm->rhs->accept(this);
    isUnsigned = false;
    out << "STOc\n";
}

void R::CodegenVisitor::visit(AdvanceStatement* stm) {
    VarType type = env.getVariableValue(stm->id).value();
    out << "LDA " << stm->id << "\n";
    if (type == VarType::UINT32_TYPE || type == VarType::UINT64_TYPE) {
        isUnsigned = true;
    }
    stm->rhs->accept(this);
    isUnsigned = false;
    out << "INCc\n";
}

void R::CodegenVisitor::visit(ReturnStatement* stm) {
    if (stm->exp) {
        stm->exp->accept(this);
        // RETv is for return top of stack
        out << "RETv\n";
    }
    else {
        // RETn is for return nothing
        out << "RETn\n";
    }
}

void R::CodegenVisitor::visit(PrintStatement* stm) {
    for (auto it = stm->expList.begin(); it != stm->expList.end(); it++) {
        (*it)->accept(this);
        out << "PRINT\n";
    }
}

void R::CodegenVisitor::visit(IfStatement* stm) {
    if (stm->elseBody) {
        string L1 = nextLabel(), L2 = nextLabel();
        stm->condition->accept(this);
        out << "FJP " << L1 << "\n";
        stm->ifBody->accept(this);
        out << "UJP " << L2 << "\n";
        out << L1 << "\n";
        stm->elseBody->accept(this);
        out << L2 << "\n";
    }
    else {
        string L1 = nextLabel();
        stm->condition->accept(this);
        out << "FJP " << L1 << "\n";
        stm->ifBody->accept(this);
        out << L1 << "\n";
    }
}

void R::CodegenVisitor::visit(WhileStatement* stm) {
    string L1 = nextLabel(), L2 = nextLabel();
    out << L1 << "\n";
    stm->condition->accept(this);
    out << "FJP " << L2 << "\n";
    stm->body->accept(this);
    out << "UJP " << L1 << "\n";
    out << L2 << "\n";
}

void R::CodegenVisitor::visit(ForStatement* stm) {
    out << "MST\n";
    env.addLevel();

    string L1 = nextLabel(), L2 = nextLabel();
    env.addVariable(stm->id, VarType::INT32_TYPE);
    
    out << "LDA " << stm->id << "\n";
    stm->start->accept(this);
    out << "STOc\n";

    out << L1 << "\n";
    out << "LODc " << stm->id << "\n";
    stm->end->accept(this);
    out << "LESc\n";
    out << "FJP " << L2 << "\n";

    stm->body->accept(this);

    out << "LDA " << stm->id << "\n";
    out << "LDCc 1\n";
    out << "INCc\n";
    out << "UJP " << L1 << "\n";
    out << L2 << "\n";

    env.removeLevel();
    out << "RET\n";
}

void R::CodegenVisitor::visit(UnsafeStatement* stm) {
    stm->body->accept(this);
}

void R::CodegenVisitor::visit(ScopeStatement* stm) {
    stm->body->accept(this);
}

// Exp

R::IVisitorReturn* R::CodegenVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    exp->right->accept(this);
    char arithmetic = isUnsigned ? 'U' : 'I';
    switch (exp->op) {
        // Arithmetic operators
        case PLUS_OP: out << "AD" << arithmetic; break;
        case MINUS_OP: out << "SB" << arithmetic; break;
        case MUL_OP: out << "MP" << arithmetic; break;
        case DIV_OP: out << "DV" << arithmetic; break;
        // Boolean operators
        case LESS_OP: out << "LESc"; break;
        case LESS_EQ_OP: out << "LEQc"; break;
        case GREATER_OP: out << "GRTc"; break;
        case GREATER_EQ_OP: out << "GEQc"; break; 
        case EQUALS_OP: out << "EQUc"; break;
        case NEQUALS_OP: out << "NEQc"; break;
    }
    out << "\n";
    return nullptr;
}

R::IVisitorReturn* R::CodegenVisitor::visit(UnaryExp* exp) {
    exp->exp->accept(this);
    switch (exp->op) {
        // Arithmetic operators
        case NEG_OP: out << "NGI"; break;
        // Boolean operators
        case NOT_OP: out << "NOT"; break;
    }
    out << "\n";
    return nullptr;
}

R::IVisitorReturn* R::CodegenVisitor::visit(IntegerExp* exp) {
    out << "LDCc ";
    switch (exp->type) {
        case VarType::INT32_TYPE: out << get<int32_t>(exp->value); break;
        case VarType::INT64_TYPE: out << get<int64_t>(exp->value); break;
        case VarType::UINT32_TYPE: out << get<uint32_t>(exp->value); break;
        case VarType::UINT64_TYPE: out << get<uint64_t>(exp->value); break;
        case VarType::BOOL_TYPE: out << get<bool>(exp->value); break;
        default: {
            string msg = "Error: Tipo no reconocido - " + varTypeToString(exp->type);
            throw runtime_error(msg);
        }
    }
    out << "\n";
    return nullptr;
}

R::IVisitorReturn* R::CodegenVisitor::visit(IdentifierExp* exp) {
    out << "LODc " << exp->name << "\n";
    return nullptr;
}

R::IVisitorReturn* R::CodegenVisitor::visit(FunctionExp* exp) {
    // MSTp is mark stack for procedure
    out << "MSTp\n";
    for (auto it = exp->args.begin(); it != exp->args.end(); it++) {
        (*it)->accept(this);
    }
    out << "CUP " << exp->name << "\n";
    return nullptr;
}
