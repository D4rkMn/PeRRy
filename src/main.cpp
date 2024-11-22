#include <iostream>
#include <fstream>
#include <string>
#include <R/Compiler.h>
using namespace std;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cout << "Numero incorrecto de argumentos. Uso: " << argv[0] << " <archivo_de_entrada>" << endl;
        exit(1);
    }

    string file(argv[1]);

    R::Compiler compiler(true);
    compiler.setInputFile(file);
    compiler.setOutputFile("output/output.txt");
    compiler.compile();

    return 0;
}