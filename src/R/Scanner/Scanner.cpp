#include <iostream>
#include <cstring>

#include "R/Token/Token.h"
#include "R/Scanner/Scanner.h"
using namespace std;

void R::Scanner::setInput(const string& _input) {
    reset();
    input = _input;
}

void R::Scanner::resetInput() {
    input = "";
    reset();
}

bool R::Scanner::isWhiteSpace(char c) const {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool R::Scanner::isNewline(char c) const {
    return c == '\n' || c == '\r';
}

void R::Scanner::reset() {
    first = 0;
    current = 0;
    line = 1;
}

void R::Scanner::backtrack() {
    auto h = history.top();
    first = h.first;
    current = h.current;
    line = h.line;
    history.pop();
}

void R::Scanner::test() const {
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