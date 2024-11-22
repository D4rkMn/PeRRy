#include <iostream>
#include "R/Visitor/IVisitor.h"

#include "R/ASTNodes/Program.h"
#include "R/ASTNodes/Function.h"
#include "R/ASTNodes/Stm.h"
#include "R/ASTNodes/Exp.h"
using namespace std;

// Program

void R::LetVar::accept(IVisitor* v) {
    v->visit(this);
}

void R::StaticVar::accept(IVisitor* v) {
    v->visit(this);
}

void R::ConstVar::accept(IVisitor* v) {
    v->visit(this);
}

void R::Body::accept(IVisitor* v) {
    v->visit(this);
}

void R::Program::accept(IVisitor* v) {
    v->visit(this);
}

// Function

void R::ParamDec::accept(IVisitor* v) {
    v->visit(this);
}

void R::ParamDecList::accept(IVisitor* v) {
    v->visit(this);
}

void R::Function::accept(IVisitor* v) {
    v->visit(this);
}

// Stm

void R::ExpStatement::accept(IVisitor* v) {
    v->visit(this);
}

void R::AssignStatement::accept(IVisitor* v) {
    v->visit(this);
}

void R::AdvanceStatement::accept(IVisitor* v) {
    v->visit(this);
}

void R::ReturnStatement::accept(IVisitor* v) {
    v->visit(this);
}

void R::PrintStatement::accept(IVisitor* v) {
    v->visit(this);
}

void R::IfStatement::accept(IVisitor* v) {
    v->visit(this);
}

void R::WhileStatement::accept(IVisitor* v) {
    v->visit(this);
}

void R::ForStatement::accept(IVisitor* v) {
    v->visit(this);
}

void R::UnsafeStatement::accept(IVisitor* v) {
    v->visit(this);
}

void R::ScopeStatement::accept(IVisitor* v) {
    v->visit(this);
}

// Exp

R::IVisitorReturn* R:: BinaryExp::accept(IVisitor* v) {
    return v->visit(this);
}

R::IVisitorReturn* R:: UnaryExp::accept(IVisitor* v) {
    return v->visit(this);
}

R::IVisitorReturn* R:: IntegerExp::accept(IVisitor* v) {
    return v->visit(this);
}

R::IVisitorReturn* R:: IdentifierExp::accept(IVisitor* v) {
    return v->visit(this);
}

R::IVisitorReturn* R:: FunctionExp::accept(IVisitor* v) {
    return v->visit(this);
}