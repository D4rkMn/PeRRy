#include "P/Interpreter.h"
#include "P/Instruction/Program.h"
using namespace std;

void P::Interpreter::setInputFile(const std::string& _input) {
    inputFile = std::ifstream(_input);
    if (!inputFile.is_open()) {
        string msg = "Error: No se pudo abrir el archivo: '" + _input + "'";
        throw runtime_error(msg);
    }
}

void P::Interpreter::interpret() {
    if (isDebug) cout << "\nIniciando P::Interpreter:\n\n";

    // get input file's code
    string code = "";
    string line = "";
    while (getline(inputFile, line)) {
        code += line + '\n';
    }
    inputFile.close();

    parser.isDebug = interpreter.isDebug = isDebug;

    scanner.setInput(code);
    if (isDebug) scanner.test();

    parser.setScanner(&scanner);
    Program* program = parser.parseProgram();

    interpreter.interpret(program);
    delete program;
}