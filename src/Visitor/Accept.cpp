#include <iostream>
#include "Visitor/IVisitor.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

// Program

void LetVar::accept(IVisitor* v) {
    v->visit(this);
}

void StaticVar::accept(IVisitor* v) {
    v->visit(this);
}

void ConstVar::accept(IVisitor* v) {
    v->visit(this);
}

void Body::accept(IVisitor* v) {
    v->visit(this);
}

void Program::accept(IVisitor* v) {
    v->visit(this);
}

// Function

void ParamDec::accept(IVisitor* v) {
    v->visit(this);
}

void ParamDecList::accept(IVisitor* v) {
    v->visit(this);
}

void Function::accept(IVisitor* v) {
    v->visit(this);
}

// Stm

void ExpStatement::accept(IVisitor* v) {
    v->visit(this);
}

void AssignStatement::accept(IVisitor* v) {
    v->visit(this);
}

void AdvanceStatement::accept(IVisitor* v) {
    v->visit(this);
}

void ReturnStatement::accept(IVisitor* v) {
    v->visit(this);
}

void PrintStatement::accept(IVisitor* v) {
    v->visit(this);
}

void IfStatement::accept(IVisitor* v) {
    v->visit(this);
}

void ForStatement::accept(IVisitor* v) {
    v->visit(this);
}

void UnsafeStatement::accept(IVisitor* v) {
    v->visit(this);
}

void ScopeStatement::accept(IVisitor* v) {
    v->visit(this);
}

// Exp

IVisitorReturn* BinaryExp::accept(IVisitor* v) {
    return v->visit(this);
}

IVisitorReturn* IntegerExp::accept(IVisitor* v) {
    return v->visit(this);
}

IVisitorReturn* BoolExp::accept(IVisitor* v) {
    return v->visit(this);
}

IVisitorReturn* IdentifierExp::accept(IVisitor* v) {
    return v->visit(this);
}

IVisitorReturn* FunctionExp::accept(IVisitor* v) {
    return v->visit(this);
}