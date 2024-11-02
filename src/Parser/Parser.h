#ifndef PARSER_H
#define PARSER_H

#include "Scanner/Scanner.h"

class Parser {
private:
    
    Scanner* scanner;
    Token *current, *previous;

    bool advance();
    bool isAtEnd();

    bool match(Token::Type);
    bool check(Token::Type);

public:

    Parser(Scanner*);
    ~Parser() = default;

};

#endif // PARSER_H