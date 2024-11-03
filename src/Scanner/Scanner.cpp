#include <iostream>
#include <cstring>

#include "Token/Token.h"
#include "Scanner/Scanner.h"

using namespace std;

Scanner::Scanner(const char* s) : input(s), first(0), current(0), line(1) {}
Scanner::~Scanner() {}

bool Scanner::isWhiteSpace(char c) const {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool Scanner::isNewline(char c) const {
    return c == '\n' || c == '\r';
}

void Scanner::reset() {
    first = 0;
    current = 0;
}

void Scanner::test() const {
    string inputCopy = input;
    Scanner testScanner(inputCopy.c_str());
    testScanner.isTestScanner = true;
    Token* current;
    cout << "Iniciando Test Scanner:\n\n";
    cout << "Línea 1:\n";
    while ((current = testScanner.nextToken())->type != Token::END) {
        if (current->type == Token::ERR) {
            string msg = "Error: Carácter inválido: '" + current->text + "' - línea " + to_string(line);
            throw runtime_error(msg);
        } else {
            cout << *current << "\n";
        }
        delete current;
    }
    cout << "TOKEN(END)\n";
    delete current;
    cout << "Scanner exitoso\n\n";
}