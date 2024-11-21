#include <iostream>
#include "Visitor/CodegenVisitor/CodegenVisitor.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

void CodegenVisitor::generate(Program* program) {
    cout << "Generando código:\n";
    program->accept(this);
    cout << "Codegen exitoso\n\n";
}

// Program

void CodegenVisitor::visit(Program* program) {
    for (auto it = program->programList.begin(); it != program->programList.end(); it++) {
        (*it)->accept(this);
    }
}

void CodegenVisitor::visit(Body* body) {
    for (auto it = body->bodyList.begin(); it != body->bodyList.end(); it++) {
        (*it)->accept(this);
    }
}

void CodegenVisitor::visit(LetVar* vardec) {
    
}

void CodegenVisitor::visit(StaticVar* vardec) {
    
}

void CodegenVisitor::visit(ConstVar* vardec) {
    // nothing to output
}

// Function

// TODO:
void CodegenVisitor::visit(Function* function) {
    function->body->accept(this);
}

void CodegenVisitor::visit(ParamDecList* params) {
    // nothing to output
}

void CodegenVisitor::visit(ParamDec* param) {
    // nothing to output
}

// Stm

void CodegenVisitor::visit(ExpStatement* stm) {

}

void CodegenVisitor::visit(AssignStatement* stm) {

}

void CodegenVisitor::visit(AdvanceStatement* stm) {

}

void CodegenVisitor::visit(ReturnStatement* stm) {

}

void CodegenVisitor::visit(PrintStatement* stm) {

}

void CodegenVisitor::visit(IfStatement* stm) {

}

void CodegenVisitor::visit(WhileStatement* stm) {

}

void CodegenVisitor::visit(ForStatement* stm) {

}

void CodegenVisitor::visit(UnsafeStatement* stm) {

}

void CodegenVisitor::visit(ScopeStatement* stm) {

}

// Exp

IVisitorReturn* CodegenVisitor::visit(BinaryExp* exp) {

}

IVisitorReturn* CodegenVisitor::visit(UnaryExp* exp) {

}

IVisitorReturn* CodegenVisitor::visit(IntegerExp* exp) {

}

IVisitorReturn* CodegenVisitor::visit(IdentifierExp* exp) {

}

IVisitorReturn* CodegenVisitor::visit(FunctionExp* exp) {

}
