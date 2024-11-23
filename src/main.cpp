#include <iostream>
#include <fstream>
#include <string>
#include <R/Compiler.h>

#include "P/Scanner/Scanner.h"
#include "P/Parser/Parser.h"
using namespace std;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cout << "Numero incorrecto de argumentos. Uso: " << argv[0] << " <archivo_de_entrada>" << endl;
        exit(1);
    }

    string file(argv[1]);

    string outputFile = "output/output.txt";
    ifstream xd(outputFile);

    // get input file's code
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
    parser.parseProgram();

    return 0;

    R::Compiler compiler(true);
    compiler.setInputFile(file);
    compiler.setOutputFile(outputFile);
    compiler.compile();

    return 0;
}