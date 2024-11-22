#ifndef R_IVISITOR_H
#define R_IVISITOR_H

#include "R/Namespace.h"

class R::IVisitor {
public:
    bool isDebug = true;
    // Program
    virtual void visit(R::Program*) = 0;
    virtual void visit(R::Body*) = 0;
    virtual void visit(R::LetVar*) = 0;
    virtual void visit(R::StaticVar*) = 0;
    virtual void visit(R::ConstVar*) = 0;
    // Function
    virtual void visit(R::Function*) = 0;
    virtual void visit(R::ParamDecList*) = 0;
    virtual void visit(R::ParamDec*) = 0;
    // Stm
    virtual void visit(R::ExpStatement*) = 0;
    virtual void visit(R::AssignStatement*) = 0;
    virtual void visit(R::AdvanceStatement*) = 0;
    virtual void visit(R::ReturnStatement*) = 0;
    virtual void visit(R::PrintStatement*) = 0;
    virtual void visit(R::IfStatement*) = 0;
    virtual void visit(R::WhileStatement*) = 0;
    virtual void visit(R::ForStatement*) = 0;
    virtual void visit(R::UnsafeStatement*) = 0;
    virtual void visit(R::ScopeStatement*) = 0;
    // Exp
    virtual IVisitorReturn* visit(R::BinaryExp*) = 0;
    virtual IVisitorReturn* visit(R::UnaryExp*) = 0;
    virtual IVisitorReturn* visit(R::IntegerExp*) = 0;
    virtual IVisitorReturn* visit(R::IdentifierExp*) = 0;
    virtual IVisitorReturn* visit(R::FunctionExp*) = 0;
};

#endif