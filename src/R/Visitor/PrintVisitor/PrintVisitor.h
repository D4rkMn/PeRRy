#ifndef R_PRINTVISITOR_H
#define R_PRINTVISITOR_H

#include "R/Visitor/IVisitor.h"
#include <iostream>

class R::PrintVisitor : public IVisitor {
private:
    size_t indent = 0;
    void printIndent() const;
public:
    void print(Program*);
    // Program
    void visit(Program*) override;
    void visit(Body*) override;
    void visit(LetVar*) override;
    void visit(StaticVar*) override;
    void visit(ConstVar*) override;
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
    void visit(WhileStatement*) override;
    void visit(ForStatement*) override;
    void visit(UnsafeStatement*) override;
    void visit(ScopeStatement*) override;
    // Exp
    IVisitorReturn* visit(BinaryExp*) override;
    IVisitorReturn* visit(UnaryExp*) override;
    IVisitorReturn* visit(IntegerExp*) override;
    IVisitorReturn* visit(IdentifierExp*) override;
    IVisitorReturn* visit(FunctionExp*) override;
};

#endif