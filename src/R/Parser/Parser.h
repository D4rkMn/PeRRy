#ifndef R_PARSER_H
#define R_PARSER_H

#include <iostream>
#include "R/Scanner/Scanner.h"
#include "R/ASTNodes/ISharedASTNode.h"
#include "R/ASTNodes/Exp.h"
#include "R/Utility/VarType.h"
#include "R/Namespace.h"

class R::Parser {
private:
    
    Scanner* scanner = nullptr;
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

    Parser() = default;
    ~Parser() = default;

    bool isDebug = true;
    void setScanner(Scanner* s);
    void resetScanner();
    Program* parseProgram();

};

#endif