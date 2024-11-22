#ifndef R_CODEGENVISITOR_H
#define R_CODEGENVISITOR_H

#include "R/Visitor/IVisitor.h"
#include "R/Environment/Environment.h"
#include "R/Utility/VarType.h"
#include <sstream>
#include <fstream>

class R::CodegenVisitor : public IVisitor {
private:
    Environment<VarType> env;
    uint64_t labels = 0;
    std::string nextLabel();
    std::stringstream out;
    bool isUnsigned = false;
public:
    void generate(Program*);
    void output(std::ofstream&);
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