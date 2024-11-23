#include <iostream>
#include <cstring>

#include "P/Token/Token.h"
#include "P/Scanner/Scanner.h"
using namespace std;

void P::Scanner::setInput(const string& _input) {
    reset();
    input = _input;
}

void P::Scanner::resetInput() {
    input = "";
    reset();
}

bool P::Scanner::isWhiteSpace(char c) const {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool P::Scanner::isNewline(char c) const {
    return c == '\n' || c == '\r';
}

void P::Scanner::reset() {
    first = 0;
    current = 0;
    line = 1;
}

bool P::Scanner::isLabel(const string& s) const {
    if (s.size() < 2) return false;
    if (s[0] != 'L') return false;
    for (size_t i = 1; i < s.size(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

void P::Scanner::test() const {
    string inputCopy = input;
    Scanner testScanner; testScanner.setInput(input);
    testScanner.isTestScanner = true;
    Token* current;
    cout << "Iniciando Test Scanner:\n\n";
    cout << "Línea 1:\n";
    while ((current = testScanner.nextToken())->type != Token::END) {
        if (current->type == Token::ERR) {
            string msg = "Error: Carácter inválido: '" + current->text + "' - línea " + to_string(testScanner.line);
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