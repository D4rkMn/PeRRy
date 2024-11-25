#include <iostream>
#include <fstream>
#include <string>
#include <R/Compiler.h>
#include <P/Interpreter.h>
using namespace std;

int main(int argc, const char* argv[]) {
    if (argc != 3 && argc != 4) {
        cout << "\n./PeRRy <input> <output> [T|F]\n" << endl;
        exit(1);
    }
    
    bool isDebug = true;
    if (argc == 4) {
        string arg3(argv[3]);
        if (arg3 != "T" && arg3 != "F") {
            cout << "\n./PeRRy <input> <output> [T|F]\n" << endl;
            exit(1);
        }
        isDebug = (arg3 == "T");
    }
    string inputFile(argv[1]);
    string outputFile (argv[2]);

    R::Compiler compiler(isDebug);
    compiler.setInputFile(inputFile);
    compiler.setOutputFile(outputFile);
    compiler.compile();

    P::Interpreter interpreter(isDebug);
    interpreter.setInputFile(outputFile);
    interpreter.interpret();
    
    return 0;
}