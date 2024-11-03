#include <iostream>
#include "Visitor/PrintVisitor.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

void PrintVisitor::print(Program* program) {
    cout << "Imprimiendo programa:\n\n";
    program->accept(this);
}

// Program
void PrintVisitor::visit(Program* program) {
    for (auto it = program->programList.begin(); it != program->programList.end(); it++) {
        (*it)->accept(this);
        cout << "\n";
    }
}

void PrintVisitor::visit(Body* body) {
    for (auto it = body->bodyList.begin(); it != body->bodyList.end(); it++) {
        (*it)->accept(this);
        cout << "\n";
    }
}

void PrintVisitor::visit(VarDec* vardec) {
    cout << "let ";
    if (vardec->mut) cout << "mut ";
    cout << vardec->id << " ";
    if (vardec->type != UNKNOWN_TYPE) {
        cout << ": " << varTypeToString(vardec->type) << " ";
    }
    if (vardec->exp) {
        cout << "= " << vardec->exp->accept(this);
    }
    cout << ";";
}

// Function
void PrintVisitor::visit(Function* function) {
    cout << "fn " << function->id << "(";
    if (function->params) {
        function->params->accept(this);
    }
    cout << ")";
    if (function->type != VOID_TYPE) {
        cout << " -> " << varTypeToString(function->type) << " ";
    }
    cout << "{\n";
    function->body->accept(this);
    cout << "}";
}

void PrintVisitor::visit(ParamDecList* params) {
    for (auto it = params->params.begin(); it != params->params.end(); it++) {
        if (it != params->params.begin()) cout << ", ";
        it->accept(this);
    }
}

void PrintVisitor::visit(ParamDec* param) {
    cout << param->id << " : " << varTypeToString(param->type);
}

// Stm
void PrintVisitor::visit(ExpStatement* stm) {
    stm->exp->accept(this);
    cout << ";";
}

void PrintVisitor::visit(AssignStatement* stm) {
    cout << stm->id << " = ";
    stm->rhs->accept(this);
    cout << ";";
}

void PrintVisitor::visit(AdvanceStatement* stm) {
    cout << stm->id << " += ";
    stm->rhs->accept(this);
    cout << ";";
}

void PrintVisitor::visit(ReturnStatement* stm) {
    cout << "return ";
    stm->exp->accept(this);
    cout << ";";
}

void PrintVisitor::visit(PrintStatement* stm) {
    cout << "println!(" << '"' << stm->textLiteral << '"';
    for (auto it = stm->expList.begin(); it != stm->expList.end(); it++) {
        cout << ", ";
        (*it)->accept(this);
    }
    cout << ")";
}

void PrintVisitor::visit(IfStatement* stm) {
    cout << "if ";
    stm->condition->accept(this);
    cout << " {\n";
    stm->ifBody->accept(this);
    cout << "}";
    if (!stm->elseBody) return;
    cout << "\nelse {\n";
    stm->elseBody->accept(this);
    cout << "}";
}

void PrintVisitor::visit(ForStatement* stm) {
    cout << "for " << stm->id << " in ";
    stm->start->accept(this);
    cout << "..";
    stm->end->accept(this);
    cout << " {\n";
    stm->body->accept(this);
    cout << "}";
}

// Exp
void PrintVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << " " << Exp::binopToString(exp->op) << " ";
    exp->right->accept(this);
}

void PrintVisitor::visit(IntegerExp* exp) {
    cout << exp->value;
}

void PrintVisitor::visit(IdentifierExp* exp) {
    cout << exp->name;
}

void PrintVisitor::visit(FunctionExp* exp) {
    cout << exp->name << "(";
    for (auto it = exp->args.begin(); it != exp->args.end(); it++) {
        if (it != exp->args.begin()) cout << ", ";
        (*it)->accept(this);
    }
    cout << ")";
}