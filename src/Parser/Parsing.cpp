#include <iostream>
#include <stdexcept>
#include "Parser/Parser.h"

#include "ASTNodes/Program.h"
#include "ASTNodes/Function.h"
#include "ASTNodes/Stm.h"
#include "ASTNodes/Exp.h"
using namespace std;

Program* Parser::parseProgram() {
    cout << "Iniciando Parser:\n";
    Program* program = new Program();
    while (!isAtEnd()) {
        if (match(Token::FUNCTION)) {
            program->add(parseFunction());
        }
        else if (match(Token::CONST)) {
            program->add(parseConstVar());
            if (!match(Token::SEMICOLON)) {
                throw SyntaxError("Se esperaba un ';' después de la declaración");
            }
        }
        else if (match(Token::STATIC)) {
            program->add(parseStaticVar());
            if (!match(Token::SEMICOLON)) {
                throw SyntaxError("Se esperaba un ';' después de la declaración");
            }
        }
        else {
            throw SyntaxError("Se esperaba una función o una declaración de variable");
        }
    }
    cout << "Parsing exitoso\n\n";
    return program;
}

Function* Parser::parseFunction() {
    if (!match(Token::ID)) {
        throw SyntaxError("Se esperaba un identificador");
    }
    string id = previous->text;
    if (!match(Token::LPAR)) {
        throw SyntaxError("Se esperaba un '(");
    }
    ParamDecList* params = nullptr;
    // Try to skip params
    if (!match(Token::RPAR)) {
        params = parseParamDecList();
        if (!match(Token::RPAR)) {
            throw SyntaxError("Se esperaba un ')'");
        }
    }
    // Get type
    VarType type = VarType::VOID_TYPE;
    if (match(Token::RARROW)) {
        if (!match(Token::INT32) && !match(Token::INT64)) {
            throw SyntaxError("Se esperaba un tipo");
        }
        type = TokenTypeToVarType(previous->type);
    }
    if (!match(Token::LBRACKET)) {
        throw SyntaxError("Se esperaba un '{'");
    }
    Body* body = parseBody();
    if (!match(Token::RBRACKET)) {
        throw SyntaxError("Se esperaba un '}'");
    }
    return new Function(id, params, type, body);
}

ParamDecList* Parser::parseParamDecList() {
    ParamDecList* params = new ParamDecList();
    bool mut = false;
    if (match(Token::MUT)) {
        mut = true;
    }
    if (!match(Token::ID_DEC)) {
        throw SyntaxError("Se esperaba un identificador + ':'");
    }
    string id = previous->text;
    if (!match(Token::INT32) && !match(Token::INT64)) {
        throw SyntaxError("Se esperaba un tipo");
    }
    VarType type = TokenTypeToVarType(previous->type);
    params->params.emplace_back(type, id, mut);
    // Keep matching params
    while (match(Token::COMMA)) {
        bool mut = false;
        if (match(Token::MUT)) {
            mut = true;
        }
        if (!match(Token::ID_DEC)) {
            throw SyntaxError("Se esperaba un identificador + ':'");
        }
        string id = previous->text;
        if (!match(Token::INT32) && !match(Token::INT64)) {
            throw SyntaxError("Se esperaba un tipo");
        }
        VarType type = TokenTypeToVarType(previous->type);
        params->params.emplace_back(type, id, mut);
    }
    return params;
}

LetVar* Parser::parseLetVar() {
    bool mut = false;
    if (match(Token::MUT)) mut = true;
    // Explicit type
    if (match(Token::ID_DEC)) {
        string id = previous->text;
        if (!match(Token::INT32) && !match(Token::INT64)) {
            throw SyntaxError("Se esperaba un tipo");
        }
        VarType type = TokenTypeToVarType(previous->type);
        // Explicit and assignment
        Exp* exp = nullptr;
        if (match(Token::ASSIGN)) {
            exp = parseCExpression();
        }
        // If non mut (const) and no assignment
        else if (!mut) {
            throw SyntaxError("Se esperaba un '=' a la variable no mutable");
        }
        return new LetVar(mut, id, type, exp);
    }
    // Inferred type
    if (!match(Token::ID)) {
        throw SyntaxError("Se esperaba un identificador");
    }
    string id = previous->text;
    if (!match(Token::ASSIGN)) {
        throw SyntaxError("Se esperaba un '='");
    }
    Exp* exp = parseCExpression();
    return new LetVar(mut, id, VarType::UNKNOWN_TYPE, exp);
}

StaticVar* Parser::parseStaticVar() {
    bool mut = false;
    if (match(Token::MUT)) mut = true;
    // Explicit type
    if (!match(Token::ID_DEC)) {
        throw SyntaxError("Se esperaba un identificador + ':'");
    }
    string id = previous->text;
    if (!match(Token::INT32) && !match(Token::INT64)) {
        throw SyntaxError("Se esperaba un tipo");
    }
    VarType type = TokenTypeToVarType(previous->type);
    if (!match(Token::ASSIGN)) {
        throw SyntaxError("Se esperaba un '='");
    }
    Exp* exp = parseCExpression();
    return new StaticVar(mut, id, type, exp);
}

ConstVar* Parser::parseConstVar() {
    // Explicit type
    if (!match(Token::ID_DEC)) {
        throw SyntaxError("Se esperaba un identificador + ':'");
    }
    string id = previous->text;
    if (!match(Token::INT32) && !match(Token::INT64)) {
        throw SyntaxError("Se esperaba un tipo");
    }
    VarType type = TokenTypeToVarType(previous->type);
    if (!match(Token::ASSIGN)) {
        throw SyntaxError("Se esperaba un '='");
    }
    Exp* exp = parseCExpression();
    return new ConstVar(id, type, exp);
}

Body* Parser::parseBody() {
    Body* body = new Body();
    while (!isAtEnd()) {
        // Exit at body's follows
        if (check(Token::RBRACKET)) {
            break;
        }
        else if (match(Token::LET)) {
            body->add(parseLetVar());
            if (!match(Token::SEMICOLON)) {
                throw SyntaxError("Se esperaba un ';' después de la declaración");
            }
        }
        else if (match(Token::CONST)) {
            body->add(parseConstVar());
            if (!match(Token::SEMICOLON)) {
                throw SyntaxError("Se esperaba un ';' después de la declaración");
            }
        }
        else {
            body->add(parseStatement());
        }
    }
    return body;
}

Stm* Parser::parseStatement() {
    // Parse if
    if (match(Token::IF)) {
        Exp* exp = parseCExpression();
        if (!match(Token::LBRACKET)) {
            throw SyntaxError("Se esperaba un '{'");
        }
        Body* ifBody = parseBody();
        if (!match(Token::RBRACKET)) {
            throw SyntaxError("Se esperaba un '}'");
        }
        Body* elseBody = nullptr;
        // Match else
        if (match(Token::ELSE)) {
            if (!match(Token::LBRACKET)) {
                throw SyntaxError("Se esperaba un '{'");
            }
            elseBody = parseBody();
            if (!match(Token::RBRACKET)) {
                throw SyntaxError("Se esperaba un '}'");
            }
        }
        return new IfStatement(exp, ifBody, elseBody);
    }
    // Parse for
    if (match(Token::FOR)) {
        if (!match(Token::ID)) {
            throw SyntaxError("Se esperaba un identificador");
        }
        string id = previous->text;
        if (!match(Token::IN)) {
            throw SyntaxError("Se esperaba 'in'");
        }
        Exp* start = parseCExpression();
        if (!match(Token::RANGE)) {
            throw SyntaxError("Se esperaba '..'");
        }
        Exp* end = parseCExpression();
        if (!match(Token::LBRACKET)) {
            throw SyntaxError("Se esperaba un '{'");
        }
        Body* body = parseBody();
        if (!match(Token::RBRACKET)) {
            throw SyntaxError("Se esperaba un '}'");
        }
        return new ForStatement(id, start, end, body);
    }
    // Parse unsafe
    if (match(Token::UNSAFE)) {
        if (!match(Token::LBRACKET)) {
            throw SyntaxError("Se esperaba un '{'");
        }
        Body* body = parseBody();
        if (!match(Token::RBRACKET)) {
            throw SyntaxError("Se esperaba un '}'");
        }
        return new UnsafeStatement(body);
    }
    // Parse scope
    if (match(Token::LBRACKET)) {
        Body* body = parseBody();
        if (!match(Token::RBRACKET)) {
            throw SyntaxError("Se esperaba un '}'");
        }
        return new ScopeStatement(body);
    }
    // Parse print
    if (match(Token::PRINTLN)) {
        if (!match(Token::LPAR)) {
            throw SyntaxError("Se esperaba un '('");
        }
        if (!match(Token::TEXT)) {
            throw SyntaxError("Se esperaba texto");
        }
        string text = previous->text;
        PrintStatement* stm = new PrintStatement(text);
        // Get print string args '{}'
        size_t args = 0;
        size_t i = 0;
        while (i < text.length() && text[i] != '"') {
            if (i+1 < text.length() && text[i] == '{' && text[i+1] == '}') {
                args++;
            }
            i++;
        }
        // Get args
        while (match(Token::COMMA)) {
            stm->expList.push_back(parseCExpression());
        }
        if (stm->expList.size() != args) {
            string msg = "Error: Se esperaban '" + to_string(args) +
                "' parámetros, pero en lugar se encontraron '" + to_string(stm->expList.size())
                + "' parámetros - línea " + to_string(current->line);
            throw runtime_error(msg);
        }
        if (!match(Token::RPAR)) {
            throw SyntaxError("Se esperaba un ')'");
        }
        if (!match(Token::SEMICOLON)) {
            throw SyntaxError("Se esperaba un ';'");
        }
        return stm;
    }
    // Parse return
    if (match(Token::RETURN)) {
        Exp* exp = nullptr;
        if (!match(Token::SEMICOLON)) {
            exp = parseCExpression();
            if (!match(Token::SEMICOLON)) {
                throw SyntaxError("Se esperaba un ';'");
            }
        }
        return new ReturnStatement(exp);
    }
    // Assign, advance, exp
    if (match(Token::ID)) {
        string id = previous->text;
        Stm* stm = nullptr;
        if (match(Token::ASSIGN)) {
            stm = new AssignStatement(id, parseCExpression());
        }
        else if (match(Token::ADVANCE)) {
            stm = new AdvanceStatement(id, parseCExpression());
        }
        else {
            backtrack();
            stm = new ExpStatement(parseCExpression());
        }
        if (!match(Token::SEMICOLON)) {
            throw SyntaxError("Se esperaba un ';'");
        }
        return stm;
    }
    try {
        Exp* exp = parseCExpression();
        if (!match(Token::SEMICOLON)) {
            throw SyntaxError("Se esperaba un ';'");
        }
        return new ExpStatement(exp);
    }
    catch (exception& e) {
        throw SyntaxError("Se esperaba un statement");
    }
}

Exp* Parser::parseCExpression() {
    Exp* left = parseExpression();
    if (
        match(Token::LESS) || match(Token::LESS_EQ) ||
        match(Token::GREATER) || match(Token::GREATER_EQ) ||
        match(Token::EQUALS) || match(Token::NEQUALS)
    ) {
        BinaryOp op = TokenTypeToBinaryOp(previous->type);
        Exp* right = parseExpression();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseExpression() {
    Exp* left = parseTerm();
    while (match(Token::PLUS) || match(Token::MINUS)) {
        BinaryOp op = TokenTypeToBinaryOp(previous->type);
        Exp* right = parseTerm();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseTerm() {
    Exp* left = parseFactor();
    while (match(Token::MUL) || match(Token::DIV)) {
        BinaryOp op = TokenTypeToBinaryOp(previous->type);
        Exp* right = parseFactor();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseFactor() {
    if (match(Token::ID)) {
        string id = previous->text;
        if (!match(Token::LPAR)) {
            return new IdentifierExp(id);
        }
        FunctionExp* function = new FunctionExp(id);
        if (match(Token::RPAR)) {
            return function;
        }
        // Parse arglist
        Exp* exp = parseCExpression();
        function->args.push_back(exp);
        while (match(Token::COMMA)) {
            exp = parseCExpression();
            function->args.push_back(exp);
        }
        if (!match(Token::RPAR)) {
            throw SyntaxError("Se esperaba un ')'");
        }
        return function;
    }
    if (match(Token::INTEGER)) {
        return new IntegerExp(stoll(previous->text));
    }
    if (match(Token::LPAR)) {
        Exp* exp = parseCExpression();
        if (!match(Token::RPAR)) {
            throw SyntaxError("Se esperaba un ')'");
        }
        return exp;
    }
    throw SyntaxError("Se esperaba una expresión");
}