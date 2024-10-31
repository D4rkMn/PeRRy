#include <iostream>
#include <cstring>

#include "Token/Token.h"
#include "Scanner/Scanner.h"

using namespace std;

Scanner::Scanner(const char* s) : input(s), first(0), current(0) {}
Scanner::~Scanner() {}

bool Scanner::isWhiteSpace(char c) const {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == (char)13;
}

void Scanner::reset() {
    first = 0;
    current = 0;
}

void Scanner::test() const {
    string inputCopy = input;
    Scanner testScanner(inputCopy.c_str());
    Token* current;
    cout << "Iniciando Scanner:" << endl<< endl;
    while ((current = testScanner.nextToken())->type != Token::END) {
        if (current->type == Token::ERR) {
            cout << "Error en scanner - carácter inválido: " << current->text << endl;
            break;
        } else {
            cout << *current << endl;
        }
        delete current;
    }
    cout << "TOKEN(END)" << endl;
    delete current;
}