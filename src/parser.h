#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "exp.h"

class Parser {
private:
    Scanner* scanner;
    Token *current, *previous;
    bool match(Token::Type ttype);
    bool check(Token::Type ttype);
    bool advance();
    bool isAtEnd();
    list<Stm*> parseStmList();
    Exp* parseCExp();
    Exp* parseExpression();
    Exp* parseTerm();
    Exp* parseFactor();
    void parseArgList(std::list<Exp*>& result);
public:
    Parser(Scanner* scanner);
    Program* parseProgram();
    Stm* parseStatement();
    StatementList* parseStatementList();
    VarDec* parseVarDec();
    VarDecList* parseVarDecList();
    ParamDecList* parseParamDecList();
    FunDec* parseFunDec();
    FunDecList* parseFunDecList();
    Body* parseBody();
    
};

#endif // PARSER_H