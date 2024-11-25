#ifndef P_INTERPRETER_H
#define P_INTERPRETER_H

#include <iostream>
#include <fstream>

// Namespace
#include "P/Namespace.h"
// Scanning
#include "P/Scanner/Scanner.h"
// Parsing
#include "P/Parser/Parser.h"
// Interpreting
#include "P/Visitor/InstructionVisitor/InstructionVisitor.h"

class P::Interpreter {
private:

    Scanner scanner;
    Parser parser;
    InstructionVisitor interpreter;

    std::ifstream inputFile;
    bool isDebug;

public:

    Interpreter(bool debug = true) : isDebug(debug) {}
    ~Interpreter() = default;

    void setInputFile(const std::string& _input);
    void interpret();

};

#endif