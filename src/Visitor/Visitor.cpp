#include <iostream>
#include "Visitor/Visitor.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

// Program

int VarDec::accept(Visitor* v) {
    v->visit(this);
}

int Body::accept(Visitor* v) {
    v->visit(this);
}

int Program::accept(Visitor* v) {
    v->visit(this);
}

// Function

int ParamDec::accept(Visitor* v) {
    v->visit(this);
}

int ParamDecList::accept(Visitor* v) {
    v->visit(this);
}

int Function::accept(Visitor* v) {
    v->visit(this);
}

// Stm

int ExpStatement::accept(Visitor* v) {
    v->visit(this);
}

int AssignStatement::accept(Visitor* v) {
    v->visit(this);
}

int AdvanceStatement::accept(Visitor* v) {
    v->visit(this);
}

int ReturnStatement::accept(Visitor* v) {
    v->visit(this);
}

int PrintStatement::accept(Visitor* v) {
    v->visit(this);
}

int IfStatement::accept(Visitor* v) {
    v->visit(this);
}

int ForStatement::accept(Visitor* v) {
    v->visit(this);
}

// Exp

int BinaryExp::accept(Visitor* v) {
    v->visit(this);
}

int IntegerExp::accept(Visitor* v) {
    v->visit(this);
}

int IdentifierExp::accept(Visitor* v) {
    v->visit(this);
}

int FunctionExp::accept(Visitor* v) {
    v->visit(this);
}