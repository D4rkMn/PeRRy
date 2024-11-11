#include <iostream>
#include "Visitor/TypeVisitor/TypeVisitor.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

void TypeVisitor::check(Program* program) {
    cout << "Verificando tipos:\n\n";
    program->accept(this);
}

// Program
void TypeVisitor::visit(Program* program) {
    
}

void TypeVisitor::visit(Body* body) {

}

void TypeVisitor::visit(VarDec* vardec) {

}

// Function
void TypeVisitor::visit(Function* function) {

}

void TypeVisitor::visit(ParamDecList* params) {

}

void TypeVisitor::visit(ParamDec* param) {

}

// Stm
void TypeVisitor::visit(ExpStatement* stm) {

}

void TypeVisitor::visit(AssignStatement* stm) {

}

void TypeVisitor::visit(AdvanceStatement* stm) {

}

void TypeVisitor::visit(ReturnStatement* stm) {

}

void TypeVisitor::visit(PrintStatement* stm) {

}

void TypeVisitor::visit(IfStatement* stm) {

}

void TypeVisitor::visit(ForStatement* stm) {

}

// Exp
IVisitorReturn* TypeVisitor::visit(BinaryExp* exp) {

}

IVisitorReturn* TypeVisitor::visit(IntegerExp* exp) {

}

IVisitorReturn* TypeVisitor::visit(IdentifierExp* exp) {

}

IVisitorReturn* TypeVisitor::visit(FunctionExp* exp) {

}