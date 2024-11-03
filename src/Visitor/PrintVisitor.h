#ifndef PRINTVISITOR_H
#define PRINTVISITOR_H

#include "Visitor/IVisitor.h"

class PrintVisitor : public IVisitor {
public:
    void print(Program*);
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
    void visit(BinaryExp*) override;
    void visit(IntegerExp*) override;
    void visit(IdentifierExp*) override;
    void visit(FunctionExp*) override;
};

#endif