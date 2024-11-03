#include <iostream>
#include "Visitor/IVisitor.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

// Program

int VarDec::accept(IVisitor* v) {
    v->visit(this);
}

int Body::accept(IVisitor* v) {
    v->visit(this);
}

int Program::accept(IVisitor* v) {
    v->visit(this);
}

// Function

int ParamDec::accept(IVisitor* v) {
    v->visit(this);
}

int ParamDecList::accept(IVisitor* v) {
    v->visit(this);
}

int Function::accept(IVisitor* v) {
    v->visit(this);
}

// Stm

int ExpStatement::accept(IVisitor* v) {
    v->visit(this);
}

int AssignStatement::accept(IVisitor* v) {
    v->visit(this);
}

int AdvanceStatement::accept(IVisitor* v) {
    v->visit(this);
}

int ReturnStatement::accept(IVisitor* v) {
    v->visit(this);
}

int PrintStatement::accept(IVisitor* v) {
    v->visit(this);
}

int IfStatement::accept(IVisitor* v) {
    v->visit(this);
}

int ForStatement::accept(IVisitor* v) {
    v->visit(this);
}

// Exp

int BinaryExp::accept(IVisitor* v) {
    v->visit(this);
}

int IntegerExp::accept(IVisitor* v) {
    v->visit(this);
}

int IdentifierExp::accept(IVisitor* v) {
    v->visit(this);
}

int FunctionExp::accept(IVisitor* v) {
    v->visit(this);
}