#ifndef P_PROGRAM_H
#define P_PROGRAM_H

#include "P/Namespace.h"
#include "P/Instruction/Instruction.h"
#include <unordered_map>
#include <vector>
#include <string>

class P::Program {
public:
    std::vector<Instruction*> instructions;
    std::unordered_map<std::string, uint64_t> jumpTable;
    Program() = default;
    ~Program() { for (size_t i = 0; i < instructions.size(); i++) delete instructions[i]; }
    void accept(IVisitor*);
};

#endif