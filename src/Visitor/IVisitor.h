#ifndef IVISITOR_H
#define IVISITOR_H

class IVisitorReturn;

// Program
class Program;
class Body;
class VarDec;
// Function
class Function;
class ParamDecList;
class ParamDec;
// Stm
class ExpStatement;
class AssignStatement;
class AdvanceStatement;
class ReturnStatement;
class PrintStatement;
class IfStatement;
class ForStatement;
// Exp
class BinaryExp;
class IntegerExp;
class IdentifierExp;
class FunctionExp;

class IVisitor {
public:
    // Program
    virtual void visit(Program*) = 0;
    virtual void visit(Body*) = 0;
    virtual void visit(VarDec*) = 0;
    // Function
    virtual void visit(Function*) = 0;
    virtual void visit(ParamDecList*) = 0;
    virtual void visit(ParamDec*) = 0;
    // Stm
    virtual void visit(ExpStatement*) = 0;
    virtual void visit(AssignStatement*) = 0;
    virtual void visit(AdvanceStatement*) = 0;
    virtual void visit(ReturnStatement*) = 0;
    virtual void visit(PrintStatement*) = 0;
    virtual void visit(IfStatement*) = 0;
    virtual void visit(ForStatement*) = 0;
    // Exp
    virtual IVisitorReturn* visit(BinaryExp*) = 0;
    virtual IVisitorReturn* visit(IntegerExp*) = 0;
    virtual IVisitorReturn* visit(IdentifierExp*) = 0;
    virtual IVisitorReturn* visit(FunctionExp*) = 0;
};

#endif