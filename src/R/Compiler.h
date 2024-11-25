#ifndef R_COMPILER_H
#define R_COMPILER_H

#include <iostream>
#include <fstream>

// Headers
#include "R/Namespace.h"
// Scanning
#include "R/Scanner/Scanner.h"
// Parsing
#include "R/Parser/Parser.h"
// Printing
#include "R/Visitor/PrintVisitor/PrintVisitor.h"
// Type checking
#include "R/Visitor/TypeVisitor/TypeVisitor.h"
// Const replacing
#include "R/Visitor/ConstVisitor/ConstVisitor.h"
// Expression reducing
#include "R/Visitor/ExpReduceVisitor/ExpReduceVisitor.h"
// Compile-time expression checking
#include "R/Visitor/CompileTimeVisitor/CompileTimeVisitor.h"
// Code generation
#include "R/Visitor/CodegenVisitor/CodegenVisitor.h"

class R::Compiler {
private:

    Scanner scanner;
    Parser parser;
    PrintVisitor printer;
    TypeVisitor typeChecker;
    ConstVisitor constReplacer;
    ExpReduceVisitor expReducer;
    CompileTimeVisitor compileTimeChecker;
    CodegenVisitor codeGenerator;

    std::ifstream inputFile;
    std::ofstream outputFile;
    bool isDebug;

public:

    Compiler(bool debug = true) : isDebug(debug) {}
    ~Compiler() = default;

    void setInputFile(const std::string& _input);
    void setOutputFile(const std::string& _output);
    void compile();

};

#endif