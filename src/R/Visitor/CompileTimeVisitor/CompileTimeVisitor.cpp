#include <iostream>
#include "R/Visitor/CompileTimeVisitor/CompileTimeVisitor.h"
#include "R/Visitor/CompileTimeVisitor/CompileTimeReturn.h"

#include "R/ASTNodes/Program.h"
#include "R/ASTNodes/Function.h"
#include "R/ASTNodes/Stm.h"
#include "R/ASTNodes/Exp.h"
using namespace std;

bool R::CompileTimeVisitor::isCompileTimeExp(Exp* exp) {
    IVisitorReturn* ret = exp->accept(this);
    if (!ret) return false;
    delete ret;
    return true;
}

runtime_error R::CompileTimeVisitor::CompileTimeError(Exp* exp) {
    string msg = "Error: La expresión no se pudo reducir en tiempo de compilación";
    return runtime_error(msg);
}

void R::CompileTimeVisitor::check(Program* program) {
    if (isDebug) cout << "Verificando expresiones de compile-time:\n\n";
    program->accept(this);
    if (isDebug) cout << "Compile-time checker exitoso\n\n";
}

// Program

void R::CompileTimeVisitor::visit(Program* program) {
    for (auto it = program->programList.begin(); it != program->programList.end(); it++) {
        (*it)->accept(this);
    }
}

void R::CompileTimeVisitor::visit(Body*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(LetVar*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(StaticVar* vardec) {
    bool result = isCompileTimeExp(vardec->exp);
    if (!result) {
        throw CompileTimeError(vardec->exp);
    }
}

void R::CompileTimeVisitor::visit(ConstVar*) {
    // nothing to check
}

// Function

void R::CompileTimeVisitor::visit(Function*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(ParamDecList*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(ParamDec*) {
    // nothing to check
}

// Stm

void R::CompileTimeVisitor::visit(ExpStatement*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(AssignStatement*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(AdvanceStatement*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(ReturnStatement*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(PrintStatement*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(IfStatement*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(WhileStatement*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(ForStatement*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(UnsafeStatement*) {
    // nothing to check
}

void R::CompileTimeVisitor::visit(ScopeStatement*) {
    // nothing to check
}

// Exp
R::IVisitorReturn* R::CompileTimeVisitor::visit(BinaryExp* exp) {
    return nullptr;
}

R::IVisitorReturn* R::CompileTimeVisitor::visit(UnaryExp* exp) {
    return nullptr;
}

R::IVisitorReturn* R::CompileTimeVisitor::visit(IntegerExp* exp) {
    return new CompileTimeReturn;
}

R::IVisitorReturn* R::CompileTimeVisitor::visit(IdentifierExp*) {
    return nullptr;
}

R::IVisitorReturn* R::CompileTimeVisitor::visit(FunctionExp*) {
    return nullptr;
}