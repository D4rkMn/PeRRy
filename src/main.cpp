#include <iostream>
#include <fstream>
#include <string>
#include <R/Compiler.h>

#include "P/Scanner/Scanner.h"
#include "P/Parser/Parser.h"
#include "P/Instruction/Program.h"
#include "P/Visitor/InstructionVisitor/InstructionVisitor.h"
using namespace std;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cout << "Numero incorrecto de argumentos. Uso: " << argv[0] << " <archivo_de_entrada>" << endl;
        exit(1);
    }

    string file(argv[1]);

    string outputFile = "output/output.txt";

    R::Compiler compiler(true);
    compiler.setInputFile(file);
    compiler.setOutputFile(outputFile);
    compiler.compile();

    // get input file's code
    ifstream xd(outputFile);
    string code = "";
    string line = "";
    while (getline(xd, line)) {
        code += line + '\n';
    }
    xd.close();

    P::Scanner scanner;
    scanner.setInput(code);
    scanner.test();

    P::Parser parser;
    parser.setScanner(&scanner);
    P::Program* program = parser.parseProgram();

    for (auto it = program->jumpTable.begin(); it != program->jumpTable.end(); it++) {
        cout << it->first << " : " << it->second << "\n";
    } cout << "\n";

    P::InstructionVisitor interpreter;    
    interpreter.interpret(program);
    return 0;
}