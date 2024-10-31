#include <iostream>
#include <stdexcept>
#include "token.h"
#include "scanner.h"
#include "exp.h"
#include "parser.h"

using namespace std;

bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return current->type == ttype;
}

bool Parser::advance() {
    if (!isAtEnd()) {
        Token* temp = current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR)) {
            cout << "Error de análisis, carácter no reconocido: " << current->text << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd() {
    return (current->type == Token::END);
}

Parser::Parser(Scanner* sc):scanner(sc) {
    previous = NULL;
    current = scanner->nextToken();
    if (current->type == Token::ERR) {
        cout << "Error en el primer token: " << current->text << endl;
        exit(1);
    }
}

VarDec* Parser::parseVarDec() {
    VarDec* vd = NULL;
    if (match(Token::VAR)) {
        if (!match(Token::ID)) {
            cout << "Error: se esperaba un identificador después de 'var'." << endl;
            exit(1);
        }
        string type = previous->text;
        list<string> ids;
        if (!match(Token::ID)) {
            cout << "Error: se esperaba un identificador después de 'var'." << endl;
            exit(1);
        }
        ids.push_back(previous->text);
        while (match(Token::COMA)) {
            if (!match(Token::ID)) {
                cout << "Error: se esperaba un identificador después de ','." << endl;
                exit(1);
            }
            ids.push_back(previous->text);
        }
        if (!match(Token::PC)) {
            cout << "Error: se esperaba un ';' al final de la declaración." << endl;
            exit(1);
        }
        vd = new VarDec(type, ids);
    }
    return vd;
}

VarDecList* Parser::parseVarDecList() {
    VarDecList* vdl = new VarDecList();
    VarDec* aux;
    aux = parseVarDec();
    while (aux != NULL) {
        vdl->add(aux);
        aux = parseVarDec();
    }
    return vdl;
}

ParamDecList* Parser::parseParamDecList() {
    ParamDecList* result = new ParamDecList();
    while (true) {
        // type
        if (!match(Token::ID)) {
            break;
        }
        string type = previous->text;
        // id
        if (!match(Token::ID)) {
            cout << "Error: se esperaba un identificador después del tipo." << endl;
            exit(1);
        }
        string id = previous->text;
        result->params.emplace_back(type, id);
        if (!match(Token::COMA)) {
            break;
        }
    }
    if (result->params.size() == 0) {
        delete result;
        return nullptr;
    }
    return result;
}

FunDec* Parser::parseFunDec() {
    if (!match(Token::FUN)) {
        return nullptr;
    }
    // type
    if (!match(Token::ID)) {
        cout << "Error: Se esperaba un identificador después de 'fun'." << endl;
        exit(1);
    }
    string type = previous->text;
    // id
    if (!match(Token::ID)) {
        cout << "Error: Se esperaba un identificador después del tipo." << endl;
        exit(1);
    }
    string id = previous->text;
    if (!match(Token::PI)) {
        cout << "Error: Se esperaba un '(' después del identificador." << endl;
        exit(1);
    }
    ParamDecList* params = parseParamDecList();
    if (!match(Token::PD)) {
        cout << "Error: Se esperaba un ')' después de la declaración de tipos." << endl;
        if (params) delete params;
        exit(1);
    }
    Body* body = parseBody();
    if (!match(Token::ENDFUN)) {
        cout << "Error: Se esperaba un 'endfun' después del body." << endl;
        if (params) delete params;
        if (body) delete body;
        exit(1);
    }
    FunDec* result = new FunDec(type, id);
    result->params = params;
    result->body = body;
    return result;
}

FunDecList* Parser::parseFunDecList() {
    FunDecList* funDecList = new FunDecList();
    while (true) {
        FunDec* funDec = parseFunDec();
        if (!funDec) break;
        funDecList->add(funDec);
    }
    if (funDecList->fundecs.size() == 0) {
        cout << "Error: No se ha declarado ninguna función." << endl;
        exit(1);
    }
    return funDecList;
}

StatementList* Parser::parseStatementList() {
    StatementList* sl = new StatementList();
    sl->add(parseStatement());
    while (match(Token::PC)) {
        sl->add(parseStatement());
    }
    return sl;
}


Body* Parser::parseBody() {
    VarDecList* vdl = parseVarDecList();
    StatementList* sl = parseStatementList();
    return new Body(vdl, sl);
}


Program* Parser::parseProgram() {
    VarDecList* vardecs = parseVarDecList();
    FunDecList* fundecs = parseFunDecList();
    return new Program(vardecs, fundecs);
}

list<Stm*> Parser::parseStmList() {
    list<Stm*> slist;
    slist.push_back(parseStatement());
    while(match(Token::PC)) {
        slist.push_back(parseStatement());
    }
    return slist;
}

Stm* Parser::parseStatement() {
    Stm* s = NULL;
    Exp* e = NULL;
    Body* tb = NULL; //true case
    Body* fb = NULL; //false case

    if (current == NULL) {
        cout << "Error: Token actual es NULL" << endl;
        exit(1);
    }

    if (match(Token::ID)) {
        string lex = previous->text;

        if (!match(Token::ASSIGN)) {
            cout << "Error: se esperaba un '=' después del identificador." << endl;
            exit(1);
        }
        e = parseCExp();
        s = new AssignStatement(lex, e);
    } else if (match(Token::PRINT)) {
        if (!match(Token::PI)) {
            cout << "Error: se esperaba un '(' después de 'print'." << endl;
            exit(1);
        }
        e = parseCExp();
        if (!match(Token::PD)) {
            cout << "Error: se esperaba un ')' después de la expresión." << endl;
            exit(1);
        }
        s = new PrintStatement(e);
    }
    else if (match(Token::RETURN)) {
        if (!match(Token::PI)) {
            cout << "Error: se esperaba un '(' después de 'return'." << endl;
            exit(1);
        }
        if (match(Token::PD)) {
            s = new ReturnStatement(nullptr);
        }
        else {
            e = parseCExp();
            if (!match(Token::PD)) {
                cout << "Error: se esperaba un ')' después de la expresión." << endl;
                exit(1);
            }
            s = new ReturnStatement(e);
        }
    }
    else if (match(Token::IF)) {
        e = parseCExp();
        if (!match(Token::THEN)) {
            cout << "Error: se esperaba 'then' después de la expresión." << endl;
            exit(1);
        }
        
        tb = parseBody();

        if (match(Token::ELSE)) {
            fb = parseBody();
        }
        if (!match(Token::ENDIF)) {
            cout << "Error: se esperaba 'end' al final de la declaración." << endl;
            exit(1);
        }
        s = new IfStatement(e, tb, fb);

    }
    else if (match(Token::WHILE)) {
        e = parseCExp();
        if (!match(Token::DO)) {
            cout << "Error: se esperaba 'do' después de la expresión." << endl;
            exit(1);
        }
        tb = parseBody();
        if (!match(Token::ENDWHILE)) {
            cout << "Error: se esperaba 'endwhile' al final de la declaración." << endl;
            exit(1);
        }
        s = new WhileStatement(e, tb);

    }
    else if(match(Token::FOR)){
        if(!match(Token::PI)){
            cout << "Error: se esperaba '(' después de 'for'." << endl;
            exit(1);
        }
        Exp* start = parseCExp();
        if (!match(Token::COMA)) {
            cout << "Error: se esperaba ',' después de la expresión." << endl;
            exit(1);
        }
        Exp* end = parseCExp();
        if (!match(Token::COMA)) {
            cout << "Error: se esperaba ',' después de la expresión." << endl;
            exit(1);
        }
        Exp* step = parseCExp();
        if (!match(Token::PD)) {
            cout << "Error: se esperaba ')' después de la expresión." << endl;
            exit(1);
        }
        tb = parseBody();
        if (!match(Token::ENDFOR)) {
            cout << "Error: se esperaba 'endfor' al final de la declaración." << endl;
            exit(1);
        }
        s = new ForStatement(start, end, step, tb);
    }
    else {
        cout << "Error: Se esperaba un identificador o 'print', pero se encontró: " << *current << endl;
        exit(1);
    }
    return s;
}

Exp* Parser::parseCExp(){
    Exp* left = parseExpression();
    if (match(Token::LT) || match(Token::LE) || match(Token::EQ)){
        BinaryOp op;
        if (previous->type == Token::LT){
            op = LT_OP;
        }
        else if (previous->type == Token::LE){
            op = LE_OP;
        }
        else if (previous->type == Token::EQ){
            op = EQ_OP;
        }
        Exp* right = parseExpression();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseExpression() {
    Exp* left = parseTerm();
    while (match(Token::PLUS) || match(Token::MINUS)) {
        BinaryOp op;
        if (previous->type == Token::PLUS){
            op = PLUS_OP;
        }
        else if (previous->type == Token::MINUS){
            op = MINUS_OP;
        }
        Exp* right = parseTerm();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseTerm() {
    Exp* left = parseFactor();
    while (match(Token::MUL) || match(Token::DIV)) {
        BinaryOp op;
        if (previous->type == Token::MUL){
            op = MUL_OP;
        }
        else if (previous->type == Token::DIV){
            op = DIV_OP;
        }
        Exp* right = parseFactor();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

void Parser::parseArgList(std::list<Exp*>& result) {
    Exp* exp = parseCExp();
    result.push_back(exp);
    while (match(Token::COMA)) {
        exp = parseCExp();
        result.push_back(exp);
    }
}

Exp* Parser::parseFactor() {
    Exp* e;
    Exp* e1;
    Exp* e2;
    if (match(Token::TRUE)){
        return new BoolExp(1);
    }else if (match(Token::FALSE)){
        return new BoolExp(0);
    }
    else if (match(Token::NUM)) {
        return new NumberExp(stoi(previous->text));
    }
    else if (match(Token::ID)) {
        string name = previous->text;
        if (match(Token::PI)) {
            FunctionExp* result = new FunctionExp(name);
            if (match(Token::PD)) {
                return result;
            }
            parseArgList(result->args);
            if (!match(Token::PD)) {
                cout << "Error: Se esperaba un ')' al final de la expresión." << endl;
                exit(1);
            }
            return result;
        }
        return new IdentifierExp(name);
    }
    else if (match(Token::IFEXP)) {
        match(Token::PI);
        e=parseCExp();
        match(Token::COMA);
        e1=parseCExp();
        match(Token::COMA);
        e2=parseCExp();
        match(Token::PD);
        return new IFExp(e,e1,e2);
    }
    else if (match(Token::PI)){
        e = parseCExp();
        if (!match(Token::PD)){
            cout << "Falta paréntesis derecho" << endl;
            exit(0);
        }
        return e;
    }
    cout << "Error: se esperaba un número o identificador." << endl;
    exit(0);
}

