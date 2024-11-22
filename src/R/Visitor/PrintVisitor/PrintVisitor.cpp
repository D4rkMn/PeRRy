#include <iostream>
#include "R/Visitor/PrintVisitor/PrintVisitor.h"

#include "R/ASTNodes/Program.h"
#include "R/ASTNodes/Function.h"
#include "R/ASTNodes/Stm.h"
#include "R/ASTNodes/Exp.h"
using namespace std;

void R::PrintVisitor::printIndent() const {
    for (size_t i = 0; i < indent; i++) {
        cout << "    ";
    }
}

void R::PrintVisitor::print(Program* program) {
    cout << "Imprimiendo programa:\n\n";
    program->accept(this);
    cout << "\n";
}

// Program
void R::PrintVisitor::visit(Program* program) {
    for (auto it = program->programList.begin(); it != program->programList.end(); it++) {
        (*it)->accept(this);
        cout << "\n";
    }
}

void R::PrintVisitor::visit(Body* body) {
    indent++;
    for (auto it = body->bodyList.begin(); it != body->bodyList.end(); it++) {
        (*it)->accept(this);
        cout << "\n";
    }
    indent--;
}

void R::PrintVisitor::visit(LetVar* vardec) {
    printIndent();
    cout << "let ";
    if (vardec->mut) cout << "mut ";
    cout << vardec->id;
    if (vardec->type != VarType::UNKNOWN_TYPE) {
        cout << ": " << varTypeToString(vardec->type);
    }
    if (vardec->exp) {
        cout << " = ";
        vardec->exp->accept(this);
    }
    cout << ";";
}

void R::PrintVisitor::visit(StaticVar* vardec) {
    printIndent();
    cout << "static ";
    if (vardec->mut) cout << "mut ";
    cout << vardec->id << ": ";
    cout << varTypeToString(vardec->type) << " = ";
    vardec->exp->accept(this);
    cout << ";";
}

void R::PrintVisitor::visit(ConstVar* vardec) {
    printIndent();
    cout << "const ";
    cout << vardec->id << ": ";
    cout << varTypeToString(vardec->type) << " = ";
    vardec->exp->accept(this);
    cout << ";";
}

// Function
void R::PrintVisitor::visit(Function* function) {
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

void R::PrintVisitor::visit(ParamDecList* params) {
    for (auto it = params->params.begin(); it != params->params.end(); it++) {
        if (it != params->params.begin()) cout << ", ";
        it->accept(this);
    }
}

void R::PrintVisitor::visit(ParamDec* param) {
    if (param->mut) cout << "mut ";
    cout << param->id << ": " << varTypeToString(param->type);
}

// Stm
void R::PrintVisitor::visit(ExpStatement* stm) {
    printIndent();
    stm->exp->accept(this);
    cout << ";";
}

void R::PrintVisitor::visit(AssignStatement* stm) {
    printIndent();
    cout << stm->id << " = ";
    stm->rhs->accept(this);
    cout << ";";
}

void R::PrintVisitor::visit(AdvanceStatement* stm) {
    printIndent();
    cout << stm->id << " += ";
    stm->rhs->accept(this);
    cout << ";";
}

void R::PrintVisitor::visit(ReturnStatement* stm) {
    printIndent();
    cout << "return";
    if (stm->exp) {
        cout << " ";
        stm->exp->accept(this);
    }
    cout << ";";
}

void R::PrintVisitor::visit(PrintStatement* stm) {
    printIndent();
    cout << "println!(" << '"' << stm->textLiteral << '"';
    for (auto it = stm->expList.begin(); it != stm->expList.end(); it++) {
        cout << ", ";
        (*it)->accept(this);
    }
    cout << ");";
}

void R::PrintVisitor::visit(IfStatement* stm) {
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

void R::PrintVisitor::visit(WhileStatement* stm) {
    printIndent();
    cout << "while ";
    stm->condition->accept(this);
    cout << " {\n";
    stm->body->accept(this);
    printIndent();
    cout << "}";
}

void R::PrintVisitor::visit(ForStatement* stm) {
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

void R::PrintVisitor::visit(UnsafeStatement* stm) {
    printIndent();
    cout << "unsafe {\n";
    stm->body->accept(this);
    printIndent();
    cout << "}";
}

void R::PrintVisitor::visit(ScopeStatement* stm) {
    printIndent();
    cout << "{\n";
    stm->body->accept(this);
    printIndent();
    cout << "}";
}

// Exp

R::IVisitorReturn* R::PrintVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << " " << Exp::binopToString(exp->op) << " ";
    exp->right->accept(this);
    return nullptr;
}

R::IVisitorReturn* R::PrintVisitor::visit(UnaryExp* exp) {
    cout << Exp::unopToString(exp->op);
    exp->exp->accept(this);
    return nullptr;
}

R::IVisitorReturn* R::PrintVisitor::visit(IntegerExp* exp) {
    switch (exp->type) {
        case VarType::INT32_TYPE: cout << get<int32_t>(exp->value); break;
        case VarType::INT64_TYPE: cout << get<int64_t>(exp->value); break;
        case VarType::UINT32_TYPE: cout << get<uint32_t>(exp->value); break;
        case VarType::UINT64_TYPE: cout << get<uint64_t>(exp->value); break;
        case VarType::BOOL_TYPE: cout << boolalpha << get<bool>(exp->value); break;
        default: {
            cout << "This message should not appear.";
            break;
        }
    }
    return nullptr;
}

R::IVisitorReturn* R::PrintVisitor::visit(IdentifierExp* exp) {
    cout << exp->name;
    return nullptr;
}

R::IVisitorReturn* R::PrintVisitor::visit(FunctionExp* exp) {
    cout << exp->name << "(";
    for (auto it = exp->args.begin(); it != exp->args.end(); it++) {
        if (it != exp->args.begin()) cout << ", ";
        (*it)->accept(this);
    }
    cout << ")";
    return nullptr;
}