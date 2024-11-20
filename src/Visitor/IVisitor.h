#ifndef IVISITOR_H
#define IVISITOR_H

class IVisitorReturn;

// Program
class Program;
class Body;
class LetVar;
class StaticVar;
class ConstVar;
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
class WhileStatement;
class ForStatement;
class UnsafeStatement;
class ScopeStatement;
// Exp
class BinaryExp;
class UnaryExp;
class IntegerExp;
class IdentifierExp;
class FunctionExp;

class IVisitor {
public:
    // Program
    virtual void visit(Program*) = 0;
    virtual void visit(Body*) = 0;
    virtual void visit(LetVar*) = 0;
    virtual void visit(StaticVar*) = 0;
    virtual void visit(ConstVar*) = 0;
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
    virtual void visit(WhileStatement*) = 0;
    virtual void visit(ForStatement*) = 0;
    virtual void visit(UnsafeStatement*) = 0;
    virtual void visit(ScopeStatement*) = 0;
    // Exp
    virtual IVisitorReturn* visit(BinaryExp*) = 0;
    virtual IVisitorReturn* visit(UnaryExp*) = 0;
    virtual IVisitorReturn* visit(IntegerExp*) = 0;
    virtual IVisitorReturn* visit(IdentifierExp*) = 0;
    virtual IVisitorReturn* visit(FunctionExp*) = 0;
};

#endif