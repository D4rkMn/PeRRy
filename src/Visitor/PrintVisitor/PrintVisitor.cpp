#include <iostream>
#include "Visitor/PrintVisitor/PrintVisitor.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

void PrintVisitor::printIndent() const {
    for (size_t i = 0; i < indent; i++) {
        cout << "    ";
    }
}

void PrintVisitor::print(Program* program) {
    cout << "Imprimiendo programa:\n\n";
    program->accept(this);
    cout << "\n";
}

// Program
void PrintVisitor::visit(Program* program) {
    for (auto it = program->programList.begin(); it != program->programList.end(); it++) {
        (*it)->accept(this);
        cout << "\n";
    }
}

void PrintVisitor::visit(Body* body) {
    indent++;
    for (auto it = body->bodyList.begin(); it != body->bodyList.end(); it++) {
        (*it)->accept(this);
        cout << "\n";
    }
    indent--;
}

void PrintVisitor::visit(LetVar* vardec) {
    printIndent();
    cout << "let ";
    if (vardec->mut) cout << "mut ";
    cout << vardec->id << " ";
    if (vardec->type != VarType::UNKNOWN_TYPE) {
        cout << ": " << varTypeToString(vardec->type) << " ";
    }
    if (vardec->exp) {
        cout << "= ";
        vardec->exp->accept(this);
    }
    cout << ";";
}

void PrintVisitor::visit(StaticVar* vardec) {
    printIndent();
    cout << "static ";
    if (vardec->mut) cout << "mut ";
    cout << vardec->id << ": ";
    cout << varTypeToString(vardec->type) << " = ";
    vardec->exp->accept(this);
    cout << ";";
}

void PrintVisitor::visit(ConstVar* vardec) {
    printIndent();
    cout << "const ";
    cout << vardec->id << ": ";
    cout << varTypeToString(vardec->type) << " = ";
    vardec->exp->accept(this);
    cout << ";";
}

// Function
void PrintVisitor::visit(Function* function) {
    cout << "fn " << function->id << "(";
    if (function->params) {
        function->params->accept(this);
    }
    cout << ") ";
    if (function->type != VarType::VOID_TYPE) {
        cout << "-> " << varTypeToString(function->type) << " ";
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
    printIndent();
    stm->exp->accept(this);
    cout << ";";
}

void PrintVisitor::visit(AssignStatement* stm) {
    printIndent();
    cout << stm->id << " = ";
    stm->rhs->accept(this);
    cout << ";";
}

void PrintVisitor::visit(AdvanceStatement* stm) {
    printIndent();
    cout << stm->id << " += ";
    stm->rhs->accept(this);
    cout << ";";
}

void PrintVisitor::visit(ReturnStatement* stm) {
    printIndent();
    cout << "return ";
    if (stm->exp) stm->exp->accept(this);
    cout << ";";
}

void PrintVisitor::visit(PrintStatement* stm) {
    printIndent();
    cout << "println!(" << '"' << stm->textLiteral << '"';
    for (auto it = stm->expList.begin(); it != stm->expList.end(); it++) {
        cout << ", ";
        (*it)->accept(this);
    }
    cout << ");";
}

void PrintVisitor::visit(IfStatement* stm) {
    printIndent();
    cout << "if ";
    stm->condition->accept(this);
    cout << " {\n";
    stm->ifBody->accept(this);
    printIndent();
    cout << "}";
    if (!stm->elseBody) return;
    printIndent();
    cout << "\nelse {\n";
    stm->elseBody->accept(this);
    printIndent();
    cout << "}";
}

void PrintVisitor::visit(ForStatement* stm) {
    printIndent();
    cout << "for " << stm->id << " in ";
    stm->start->accept(this);
    cout << "..";
    stm->end->accept(this);
    cout << " {\n";
    stm->body->accept(this);
    printIndent();
    cout << "}";
}

void PrintVisitor::visit(UnsafeStatement* stm) {
    printIndent();
    cout << "unsafe {\n";
    stm->body->accept(this);
    printIndent();
    cout << "}";
}

void PrintVisitor::visit(ScopeStatement* stm) {
    printIndent();
    cout << "{\n";
    stm->body->accept(this);
    printIndent();
    cout << "}";
}

// Exp
IVisitorReturn* PrintVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << " " << Exp::binopToString(exp->op) << " ";
    exp->right->accept(this);
    return nullptr;
}

IVisitorReturn* PrintVisitor::visit(IntegerExp* exp) {
    cout << exp->value;
    return nullptr;
}

IVisitorReturn* PrintVisitor::visit(IdentifierExp* exp) {
    cout << exp->name;
    return nullptr;
}

IVisitorReturn* PrintVisitor::visit(FunctionExp* exp) {
    cout << exp->name << "(";
    for (auto it = exp->args.begin(); it != exp->args.end(); it++) {
        if (it != exp->args.begin()) cout << ", ";
        (*it)->accept(this);
    }
    cout << ")";
    return nullptr;
}