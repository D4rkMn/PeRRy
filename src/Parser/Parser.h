#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "Scanner/Scanner.h"
#include "ASTNodes/ISharedASTNode.h"
#include "ASTNodes/Exp.h"

class Program;

class Function;
class ParamDecList;
class VarDec;

class Body;
class Stm;
class Exp;

class Parser {
private:
    
    Scanner* scanner;
    Token *current, *previous;

    bool advance();
    bool isAtEnd();
    bool match(Token::Type);
    bool check(Token::Type);

    std::runtime_error SyntaxError(const std::string&) const;
    VarType TokenTypeToVarType(Token::Type) const;
    BinaryOp TokenTypeToBinaryOp(Token::Type) const;

    Function* parseFunction();
    ParamDecList* parseParamDecList();
    VarDec* parseVarDec();

    Body* parseBody();
    Stm* parseStatement();

    Exp* parseCExpression();
    Exp* parseExpression();
    Exp* parseTerm();
    Exp* parseFactor();

public:

    Parser(Scanner*);
    ~Parser() = default;
    Program* parseProgram();

};

#endif