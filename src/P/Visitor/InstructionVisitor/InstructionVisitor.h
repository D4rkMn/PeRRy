#ifndef P_INSTRUCTIONVISITOR_H
#define P_INSTRUCTIONVISITOR_H

#include "P/Namespace.h"
#include "P/Visitor/IVisitor.h"
#include "P/Environment/Environment.h"
#include "P/Instruction/Program.h"
#include "P/Visitor/InstructionVisitor/DynamicStack.h"
#include <iostream>
#include <stack>
#include <unordered_map>

class P::InstructionVisitor : public IVisitor {
private:

    DynamicStack<IStackObject*> mainStack;
    std::stack< std::pair<uint64_t, std::string> > markStack;
    std::stack< std::pair<uint64_t, std::string> > markFunctionStack;
    std::stack<uint64_t> pcStack;
    uint64_t pc = 0;
    uint64_t unique = 0;

    Program* program;
    Environment<int64_t> env;

    std::runtime_error InterpretError(const std::string&);

public:
    void interpret(Program*);
    void visit(Program*) override;
    void visit(PopInstruction*) override;
    void visit(StopInstruction*) override;
    void visit(EnterInstruction*) override;
    void visit(MarkInstruction*) override;
    void visit(ReturnInstruction*) override;
    void visit(FCallInstruction*) override;
    void visit(LoadAddressInstruction*) override;
    void visit(LoadConstInstruction*) override;
    void visit(LoadVarInstruction*) override;
    void visit(StoreStackInstruction*) override;
    void visit(IncStackInstruction*) override;
    void visit(StoreToVarInstruction*) override;
    void visit(LabelInstruction*) override;
    void visit(JumpInstruction*) override;
    void visit(BinaryOpInstruction*) override;
    void visit(UnaryOpInstruction*) override;
    void visit(PrintInstruction*) override;
};

#endif