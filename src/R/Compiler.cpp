#include "R/Compiler.h"
using namespace std;

void R::Compiler::setInputFile(const std::string& _input) {
    inputFile = std::ifstream(_input);
    if (!inputFile.is_open()) {
        string msg = "Error: No se pudo abrir el archivo: '" + _input + "'";
        throw runtime_error(msg);
    }
}

void R::Compiler::setOutputFile(const std::string& _output) {
    outputFile = std::ofstream(_output);
    if (!outputFile.is_open()) {
        string msg = "Error: No se pudo abrir el archivo: '" + _output + "'";
        throw runtime_error(msg);
    }
}

void R::Compiler::compile() {
    // get input file's code
    string code = "";
    string line = "";
    while (getline(inputFile, line)) {
        code += line + '\n';
    }
    inputFile.close();

    parser.isDebug = printer.isDebug = typeChecker.isDebug = constReplacer.isDebug =
    expReducer.isDebug = compileTimeChecker.isDebug = codeGenerator.isDebug = isDebug;

    scanner.setInput(code);
    if (isDebug) scanner.test();

    parser.setScanner(&scanner);    
    Program* program = parser.parseProgram();

    if (isDebug) printer.print(program);

    typeChecker.check(program);
    constReplacer.replace(program);
    if (isDebug) printer.print(program);

    expReducer.reduce(program);
    if (isDebug) printer.print(program);
    compileTimeChecker.check(program);

    codeGenerator.generate(program);
    if (outputFile.is_open()) {
        codeGenerator.output(outputFile);
        outputFile.close();
    }

    cout << "Compilacion exitosa\n";
}