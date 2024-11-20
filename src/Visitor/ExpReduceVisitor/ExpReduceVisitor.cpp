#include <iostream>
#include "Visitor/ExpReduceVisitor/ExpReduceVisitor.h"
#include "Visitor/ExpReduceVisitor/ReducedReturn.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

IntegerExp* ExpReduceVisitor::evalBinaryExp_b(const bool& v1, const bool& v2, BinaryOp op) const {
    // eval expression
    bool result;
    switch (op) {
        // Boolean operators
        case EQUALS_OP: result = (v1 == v2); break;
        case NEQUALS_OP: result = (v1 != v2); break;
        default: {
            string msg = "Error: Operacion binaria incompatible para bool";
            throw runtime_error(msg);
        }
    }
    return new IntegerExp(bool(result));
}

IntegerExp* ExpReduceVisitor::evalUnaryExp_b(const bool& v, UnaryOp op) const {
    // eval expression
    bool result;
    switch (op) {
        // Boolean operators
        case NOT_OP: result = !v; break;
        default: {
            string msg = "Error: Operacion unaria incompatible para bool";
            throw runtime_error(msg);
        }
    }
    return new IntegerExp(bool(result));
}

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

void ExpReduceVisitor::visit(WhileStatement* stm) {
    replaceNode(stm->condition);
    stm->body->accept(this);
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
        IntegerExp* node;
        auto v1 = left->value;
        auto v2 = right->value;
        if (holds_alternative<int32_t>(v1)) {
            node = evalBinaryExp<int32_t>(get<int32_t>(v1), get<int32_t>(v2), exp->op);
        }
        else if (holds_alternative<int64_t>(v1)) {
            node = evalBinaryExp<int64_t>(get<int64_t>(v1), get<int64_t>(v2), exp->op);
        }
        else if (holds_alternative<uint32_t>(v1)) {
            node = evalBinaryExp<uint32_t>(get<uint32_t>(v1), get<uint32_t>(v2), exp->op);
        }
        else if (holds_alternative<uint64_t>(v1)) {
            node = evalBinaryExp<uint64_t>(get<uint64_t>(v1), get<uint64_t>(v2), exp->op);
        }
        else if (holds_alternative<bool>(v1)) {
            node = evalBinaryExp_b(get<bool>(v1), get<bool>(v2), exp->op);
        }
        exp->left = exp->right = nullptr;
        delete left;
        delete right;
        return new ReducedReturn(node);
    }
    return new ReducedReturn(nullptr);
}

IVisitorReturn* ExpReduceVisitor::visit(UnaryExp* exp) {
    IntegerExp* e = getNode(exp->exp->accept(this));
    if (e) {
        auto v = e->value;
        IntegerExp* node;
        if (holds_alternative<int32_t>(v)) {
            node = evalUnaryExp<int32_t>(get<int32_t>(v), exp->op);
        }
        else if (holds_alternative<int64_t>(v)) {
            node = evalUnaryExp<int64_t>(get<int64_t>(v), exp->op);
        }
        else if (holds_alternative<uint32_t>(v)) {
            node = evalUnaryExp<uint32_t>(get<uint32_t>(v), exp->op);
        }
        else if (holds_alternative<uint64_t>(v)) {
            node = evalUnaryExp<uint64_t>(get<uint64_t>(v), exp->op);
        }
        else if (holds_alternative<bool>(v)) {
            node = evalUnaryExp_b(get<bool>(v), exp->op);
        }
        exp->exp = nullptr;
        delete e;
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