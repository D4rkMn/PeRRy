#ifndef TYPEVISITOR_H
#define TYPEVISITOR_H

#include "Visitor/IVisitor.h"
#include "Environment/Environment.h"

class TypeVisitor : public IVisitor {
private:
    Environment<int> test;
public:
    void check(Program*);
    // Program
    void visit(Program*) override;
    void visit(Body*) override;
    void visit(VarDec*) override;
    // Function
    void visit(Function*) override;
    void visit(ParamDecList*) override;
    void visit(ParamDec*) override;
    // Stm
    void visit(ExpStatement*) override;
    void visit(AssignStatement*) override;
    void visit(AdvanceStatement*) override;
    void visit(ReturnStatement*) override;
    void visit(PrintStatement*) override;
    void visit(IfStatement*) override;
    void visit(ForStatement*) override;
    // Exp
    IVisitorReturn* visit(BinaryExp*) override;
    IVisitorReturn* visit(IntegerExp*) override;
    IVisitorReturn* visit(IdentifierExp*) override;
    IVisitorReturn* visit(FunctionExp*) override;
};

#endif