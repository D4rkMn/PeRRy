#ifndef P_INSTRUCTION_H
#define P_INSTRUCTION_H

#include "P/Namespace.h"
#include <string>

namespace P {
    enum class Op {
        ADD, SUB, MUL, DIV, NEG,
        LESS, LESS_EQ, GREATER, GREATER_EQ, EQUALS, NEQUALS, NOT
    };
}

class P::Instruction {
public:
    virtual ~Instruction() = default;
    virtual void accept(IVisitor*) = 0;
};

class P::PopInstruction : public Instruction {
public:
    PopInstruction() = default;
    ~PopInstruction() = default;
    void accept(IVisitor*) override;
};

class P::StopInstruction : public Instruction {
public:
    StopInstruction() = default;
    ~StopInstruction() = default;
    void accept(IVisitor*) override;
};

class P::EnterInstruction : public Instruction {
public:
    std::string functionName;
    EnterInstruction(const std::string& s) : functionName(s) {}
    ~EnterInstruction() = default;
    void accept(IVisitor*) override;
};

class P::MarkInstruction : public Instruction {
public:
    bool functionEnter;
    MarkInstruction(bool func) : functionEnter(func) {} 
    ~MarkInstruction() = default;
    void accept(IVisitor*) override;
};

class P::ReturnInstruction : public Instruction {
public:
    enum Type { SCOPE, F_VOID, F_RET };
    Type type;
    ReturnInstruction(Type t) : type(t) {}
    ~ReturnInstruction() = default;
    void accept(IVisitor*) override;
};

class P::FCallInstruction : public Instruction {
public:
    std::string functionName;
    FCallInstruction(const std::string& s) : functionName(s) {}
    ~FCallInstruction() = default;
    void accept(IVisitor*) override;
};

class P::LoadAddressInstruction : public Instruction {
public:
    std::string id;
    LoadAddressInstruction(const std::string& s) : id(s) {}
    ~LoadAddressInstruction() = default;
    void accept(IVisitor*) override;
};

class P::LoadConstInstruction : public Instruction {
public:
    int64_t value;
    LoadConstInstruction(int64_t v) : value(v) {}
    ~LoadConstInstruction() = default;
    void accept(IVisitor*) override;
};

class P::LoadVarInstruction : public Instruction {
public:
    std::string id;
    LoadVarInstruction(const std::string& s) : id(s) {}
    ~LoadVarInstruction() = default;
    void accept(IVisitor*) override;
};

class P::StoreStackInstruction : public Instruction {
public:
    StoreStackInstruction() = default;
    ~StoreStackInstruction() = default;
    void accept(IVisitor*) override;
};

class P::IncStackInstruction : public Instruction {
public:
    IncStackInstruction() = default;
    ~IncStackInstruction() = default;
    void accept(IVisitor*) override;
};

class P::StoreToVarInstruction : public Instruction {
public:
    std::string id;
    StoreToVarInstruction(const std::string& s) : id(s) {}
    ~StoreToVarInstruction() = default;
    void accept(IVisitor*) override;
};

class P::LabelInstruction : public Instruction {
public:
    int64_t labelNum;
    LabelInstruction(int64_t v) : labelNum(v) {}
    ~LabelInstruction() = default;
    void accept(IVisitor*) override;
};

class P::JumpInstruction : public Instruction {
public:
    bool unconditional;
    std::string label;
    JumpInstruction(bool unconditional, const std::string& label) : unconditional(unconditional), label(label) {}
    ~JumpInstruction() = default;
    void accept(IVisitor*) override;
};

class P::BinaryOpInstruction : public Instruction {
public:
    Op op;
    BinaryOpInstruction(Op op) : op(op) {}
    ~BinaryOpInstruction() = default;
    void accept(IVisitor*) override;
};

class P::UnaryOpInstruction : public Instruction {
public:
    Op op;
    UnaryOpInstruction(Op op) : op(op) {}
    ~UnaryOpInstruction() = default;
    void accept(IVisitor*) override;
};

class P::PrintInstruction : public Instruction {
public:
    bool doNewLine;
    PrintInstruction(bool newline) : doNewLine(newline) {}
    ~PrintInstruction() = default;
    void accept(IVisitor*) override;
};

#endif