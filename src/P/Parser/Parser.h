#ifndef P_PARSER_H
#define P_PARSER_H

#include <iostream>
#include <list>
#include "P/Instruction/Instruction.h"
#include "P/Scanner/Scanner.h"
#include "P/Namespace.h"

class P::Parser {
private:

    Scanner* scanner = nullptr;
    Token *current, *previous;

    uint64_t pc = 0;
    std::string label = "";
    bool isJump = false;

    bool advance();
    bool isAtEnd();
    bool match(Token::Type);
    bool check(Token::Type);

    std::runtime_error SyntaxError(const std::string&) const;
    Op tokenToOp(Token) const;
    Instruction* parseInstruction();

public:

    Parser() = default;
    ~Parser() = default;

    bool isDebug = true;
    void setScanner(Scanner* s);
    void resetScanner();
    Program* parseProgram();

};

#endif