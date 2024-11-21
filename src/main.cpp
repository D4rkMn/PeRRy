#include <iostream>
#include <fstream>
#include <string>

#include "Scanner/Scanner.h"
#include "Parser/Parser.h"

#include "Visitor/PrintVisitor/PrintVisitor.h"
#include "Visitor/TypeVisitor/TypeVisitor.h"
#include "Visitor/ConstVisitor/ConstVisitor.h"
#include "Visitor/ExpReduceVisitor/ExpReduceVisitor.h"
#include "Visitor/CodegenVisitor/CodegenVisitor.h"
using namespace std;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cout << "Numero incorrecto de argumentos. Uso: " << argv[0] << " <archivo_de_entrada>" << endl;
        exit(1);
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cout << "No se pudo abrir el archivo: " << argv[1] << endl;
        exit(1);
    }

    string input;
    string line;
    while (getline(infile, line)) {
        input += line + '\n';
    }
    infile.close();

    Scanner scanner(input.c_str());
    scanner.test();

    Parser parser(&scanner);
    Program* program = parser.parseProgram();

    PrintVisitor printer;
    printer.print(program);

    TypeVisitor typeChecker;
    typeChecker.check(program);

    ConstVisitor constReplacer;
    constReplacer.replace(program);

    printer.print(program);

    ExpReduceVisitor expReducer;
    expReducer.reduce(program);

    printer.print(program);

    CodegenVisitor codegen;
    codegen.generate(program);
    return 0;
}