#include <iostream>
#include "Visitor/ExpReduceVisitor/ExpReduceVisitor.h"
#include "Visitor/ExpReduceVisitor/ReducedReturn.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

void ExpReduceVisitor::replaceNode(Exp*& e) {
    IntegerExp* exp = getNode(e->accept(this));
    if (!exp) return;
    if (e && e != exp) delete e;
    e = exp;
}

IntegerExp* ExpReduceVisitor::getNode(IVisitorReturn* ret) const {
    IntegerExp* e = dynamic_cast<ReducedReturn*>(ret)->exp;
    delete ret;
    return e;
}

IntegerExp* ExpReduceVisitor::evalBinaryExp(IntegerExp* e1, IntegerExp* e2, BinaryOp op) const {
    auto v1 = e1->value;
    auto v2 = e2->value;
    // eval expression
    long long result;
    switch (op) {
        // Arithmetic operators
        case PLUS_OP: result = v1 + v2; break;
        case MINUS_OP: result = v1 - v2; break;
        case MUL_OP: result = v1 * v2; break;
        case DIV_OP: result = v1 / v2; break;
        // Boolean operators
        case LESS_OP: result = (v1 < v2); break;
        case LESS_EQ_OP: result = (v1 <= v2); break;
        case EQUALS_OP: result = (v1 == v2); break;
        case GREATER_OP: result = (v1 > v2); break;
        case GREATER_EQ_OP: result = (v1 >= v2); break;
        case NEQUALS_OP: result = (v1 != v2); break;
        default: {
            string msg = "Error: Operacion binaria desconocida";
            throw runtime_error(msg);
        }
    }
    return new IntegerExp(result);
}

void ExpReduceVisitor::reduce(Program* program) {
    cout << "Reduciendo expresiones:\n";
    program->accept(this);
    cout << "Exp Reducer exitoso\n\n";
}

// Program

void ExpReduceVisitor::visit(Program* program) {
    for (auto it = program->programList.begin(); it != program->programList.end(); it++) {
        (*it)->accept(this);
    }
}

void ExpReduceVisitor::visit(Body* body) {
    for (auto it = body->bodyList.begin(); it != body->bodyList.end(); it++) {
        (*it)->accept(this);
    }
}

void ExpReduceVisitor::visit(LetVar* vardec) {
    if (vardec->exp) {
        replaceNode(vardec->exp);
    }
}

void ExpReduceVisitor::visit(StaticVar* vardec) {
    replaceNode(vardec->exp);
}

void ExpReduceVisitor::visit(ConstVar* vardec) {
    // Nothing to reduce
}

// Function

void ExpReduceVisitor::visit(Function* function) {
    function->body->accept(this);
}

void ExpReduceVisitor::visit(ParamDecList* params) {
    // Nothing to reduce
}

void ExpReduceVisitor::visit(ParamDec* param) {
    // Nothing to reduce
}

// Stm

void ExpReduceVisitor::visit(ExpStatement* stm) {
    replaceNode(stm->exp);
}

void ExpReduceVisitor::visit(AssignStatement* stm) {
    replaceNode(stm->rhs);
}

void ExpReduceVisitor::visit(AdvanceStatement* stm) {
    replaceNode(stm->rhs);
}

void ExpReduceVisitor::visit(ReturnStatement* stm) {
    replaceNode(stm->exp);
}

void ExpReduceVisitor::visit(PrintStatement* stm) {
    for (auto it = stm->expList.begin(); it != stm->expList.end(); it++) {
        replaceNode(*it);
    }
}

void ExpReduceVisitor::visit(IfStatement* stm) {
    replaceNode(stm->condition);
    stm->ifBody->accept(this);
    if (stm->elseBody) stm->elseBody->accept(this);
}

void ExpReduceVisitor::visit(ForStatement* stm) {
    replaceNode(stm->start);
    replaceNode(stm->end);
    stm->body->accept(this);
}

void ExpReduceVisitor::visit(UnsafeStatement* stm) {
    stm->body->accept(this);
}

void ExpReduceVisitor::visit(ScopeStatement* stm) {
    stm->body->accept(this);
}

// Exp

IVisitorReturn* ExpReduceVisitor::visit(BinaryExp* exp) {
    IntegerExp* left = getNode(exp->left->accept(this));
    IntegerExp* right = getNode(exp->right->accept(this));
    if (left) {
        exp->left = left;
    }
    if (right) {
        exp->right = right;
    }
    if (left && right) {
        IntegerExp* node = evalBinaryExp(left, right, exp->op);
        exp->left = exp->right = nullptr;
        delete left;
        delete right;
        return new ReducedReturn(node);
    }
    return new ReducedReturn(nullptr);
}

IVisitorReturn* ExpReduceVisitor::visit(IntegerExp* exp) {
    return new ReducedReturn(exp);
}

IVisitorReturn* ExpReduceVisitor::visit(IdentifierExp* exp) {
    return new ReducedReturn(nullptr);
}

IVisitorReturn* ExpReduceVisitor::visit(FunctionExp* exp) {
    for (auto it = exp->args.begin(); it != exp->args.end(); it++) {
        replaceNode(*it);
    }
    return new ReducedReturn(nullptr);
}