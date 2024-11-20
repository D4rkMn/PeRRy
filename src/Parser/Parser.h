#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "Scanner/Scanner.h"
#include "ASTNodes/ISharedASTNode.h"
#include "ASTNodes/Exp.h"
#include "Utility/VarType.h"

class Program;

class Function;
class ParamDecList;
class LetVar;
class StaticVar;
class ConstVar;

class Body;
class Stm;
class Exp;

class Parser {
private:
    
    Scanner* scanner;
    Token *current, *previous;

    bool unary = false;

    bool advance();
    bool isAtEnd();
    void backtrack();
    bool match(Token::Type);
    bool check(Token::Type);

    bool matchVarType();
    bool checkVarType();

    std::runtime_error SyntaxError(const std::string&) const;
    VarType tokenTypeToVarType(Token::Type) const;
    BinaryOp tokenTypeToBinaryOp(Token::Type) const;

    Function* parseFunction();
    ParamDecList* parseParamDecList();
    LetVar* parseLetVar();
    StaticVar* parseStaticVar();
    ConstVar* parseConstVar();

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