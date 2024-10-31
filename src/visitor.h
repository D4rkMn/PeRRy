#ifndef VISITOR_H
#define VISITOR_H
#include "exp.h"
#include "environment.h"
#include <list>

class BinaryExp;
class NumberExp;
class BoolExp;
class FunctionExp;
class IFExp;
class IdentifierExp;
class AssignStatement;
class PrintStatement;
class ReturnStatement;
class IfStatement;
class WhileStatement;
class ForStatement;
class FunDecList;
class FunDec;
class ParamDecList;
class ParamDec;
class VarDec;
class VarDecList;
class StatementList;
class Body;
class Program;

class Visitor {
public:
    virtual int visit(FunctionExp* exp) = 0;
    virtual int visit(IFExp* exp) = 0;
    virtual int visit(BinaryExp* exp) = 0;
    virtual int visit(NumberExp* exp) = 0;
    virtual int visit(BoolExp* exp) = 0;
    virtual int visit(IdentifierExp* exp) = 0;
    virtual void visit(AssignStatement* stm) = 0;
    virtual void visit(PrintStatement* stm) = 0;
    virtual void visit(ReturnStatement* stm) = 0;
    virtual void visit(IfStatement* stm) = 0;
    virtual void visit(WhileStatement* stm) = 0;
    virtual void visit(ForStatement* stm) = 0;
    virtual void visit(FunDecList*) = 0;
    virtual void visit(FunDec*) = 0;
    virtual void visit(ParamDecList*) = 0;
    virtual void visit(ParamDec*) = 0;
    virtual void visit(VarDec* stm) = 0;
    virtual void visit(VarDecList* stm) = 0;
    virtual void visit(StatementList* stm) = 0;
    virtual void visit(Body* b) = 0;
};

class PrintVisitor : public Visitor {
    int depth = 0;
    void printTabs() {
        for (int i = 0; i < depth; i++) {
            cout << "    ";
        }
    }
public:
    void imprimir(Program* program);
    int visit(FunctionExp* exp) override;
    int visit(IFExp* exp) override;
    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(BoolExp* exp) override;
    int visit(IdentifierExp* exp) override;
    void visit(AssignStatement* stm) override;
    void visit(PrintStatement* stm) override;
    void visit(ReturnStatement* stm) override;
    void visit(IfStatement* stm) override;
    void visit(WhileStatement* stm) override;
    void visit(ForStatement* stm) override;
    void visit(FunDecList*) override;
    void visit(FunDec*) override;
    void visit(ParamDecList*) override;
    void visit(ParamDec*) override;
    void visit(VarDec* stm) override;
    void visit(VarDecList* stm) override;
    void visit(StatementList* stm) override;
    void visit(Body* b) override;
};

class EVALVisitor : public Visitor {
    Environment env;
public:
    void ejecutar(Program* program);
    int visit(FunctionExp* exp) override;
    int visit(IFExp* exp) override;
    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(BoolExp* exp) override;
    int visit(IdentifierExp* exp) override;
    void visit(AssignStatement* stm) override;
    void visit(PrintStatement* stm) override;
    void visit(ReturnStatement* stm) override;
    void visit(IfStatement* stm) override;
    void visit(WhileStatement* stm) override;
    void visit(ForStatement* stm) override;
    void visit(FunDecList*) override;
    void visit(FunDec*) override;
    void visit(ParamDecList*) override;
    void visit(ParamDec*) override;
    void visit(VarDec* stm) override;
    void visit(VarDecList* stm) override;
    void visit(StatementList* stm) override;
    void visit(Body* b) override;
};

class TypeVisitor : public Visitor {
    Environment env;
public:
    void check(Program* program);
    int visit(FunctionExp* exp) override;
    int visit(IFExp* exp) override;
    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(BoolExp* exp) override;
    int visit(IdentifierExp* exp) override;
    void visit(AssignStatement* stm) override;
    void visit(PrintStatement* stm) override;
    void visit(ReturnStatement* stm) override;
    void visit(IfStatement* stm) override;
    void visit(WhileStatement* stm) override;
    void visit(ForStatement* stm) override;
    void visit(FunDecList*) override;
    void visit(FunDec*) override;
    void visit(ParamDecList*) override;
    void visit(ParamDec*) override;
    void visit(VarDec* stm) override;
    void visit(VarDecList* stm) override;
    void visit(StatementList* stm) override;
    void visit(Body* b) override;
};

#endif // VISITOR_H