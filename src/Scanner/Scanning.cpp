#include <iostream>
#include <cstring>

#include "Token/Token.h"
#include "Scanner/Scanner.h"

using namespace std;

Token* Scanner::nextToken() {
    Token* token;
    history.push({first, current, line});

    // Skip empty characters
    while (current < input.length() && isWhiteSpace(input[current])) {
        if (isNewline(input[current])) {
            line++;
            if (isTestScanner) cout << "\nLínea " << line << ":\n";
        }
        current++;
    }
    
    // End of file
    if (current >= input.length()) {
        return new Token(Token::END, line);
    }

    char c = input[current];
    first = current;

    // Integer literal
    if (isdigit(c)) {
        current++;
        while (current < input.length() && isdigit(input[current])) {
            current++;
        }
        token = new Token(Token::INTEGER, input, first, current - first, line);
        VarType varType = VarType::UNKNOWN_TYPE;
        // Fetch for type suffix annotation
        if (input[current] != ' ') {
            Token* t = nextToken();
            if (t->isVarType()) {
                varType = t->toVarType();
                if (varType == VarType::BOOL_TYPE) {
                    backtrack();
                }
            }
            else {
                backtrack();
            }
        }
        token->varType = varType;
        return token;
    }

    // Reserved keywords + Id
    if (isalpha(c) || c == '_') {
        current++;
        while (current < input.length() && (isalnum(input[current]) || input[current] == '_')) {
            current++;
        }
        string word = input.substr(first, current - first);
        // Fetch for reserved keywords
        Token::Type type = Token::wordToToken(word);
        if (type != Token::ERR) {
            return new Token(type, word, 0, word.length(), line);
        }
        // Edge case: "println!"
        if (word == "println" && current < input.length() && input[current] == '!') {
            current++;
            return new Token(Token::PRINTLN, word, 0, word.length(), line);
        }
        // Edge case: Identifier with explicit type (':')
        if (current < input.length() && input[current] == ':') {
            current++;
            return new Token(Token::ID_DEC, word, 0, word.length(), line);
        }
        // Return identifier
        return new Token(Token::ID, word, 0, word.length(), line);
    }

    // Text literals
    if (c == '"') {
        current++;
        while (current < input.length() && input[current] != '"') {
            current++;
        }
        if (current >= input.length()) {
            string msg = "Error: String cerrado incorrectamente! - línea " + to_string(line);
            throw runtime_error(msg);
        }
        current++;
        string word = input.substr(first, current - first);
        return new Token(Token::TEXT, word, 1, word.length()-2, line);
    }

    // Comments
    else if (c == '/') {
        // Single line comment
        if (input[current+1] == '/') {
            current++;
            while (current < input.length() && input[current] != '\n' && input[current] != (char)13) {
                current++;
            }
            return nextToken();
        }
        /* Multi line comment */
        else if (input[current+1] == '*') {
            current++;
            while (current < input.length()) {
                if (input[current-1] == '*' && input[current] == '/') break;
                current++;
            }
            current += 2;
            return nextToken();
        }
        // Edge case: Division
        else {
            token = new Token(Token::DIV, c, line);
            current++;
        }
    }

    // Handle symbols
    if (strchr("+-*/(){}=;:.,<>!", c)) {
        switch(c) {
            case '+': {
                if (current+1 < input.length() && input[current+1] == '=') {
                    token = new Token(Token::ADVANCE, c, line);
                    current++;
                }
                else {
                    token = new Token(Token::PLUS, c, line);
                }
                break;
            }
            case '-': {
                if (current+1 < input.length() && input[current+1] == '>') {
                    token = new Token(Token::RARROW, "->", 0, 2, line);
                    current++;
                }
                else {
                    token = new Token(Token::MINUS, c, line);
                }
                break;
            }
            case '*': token = new Token(Token::MUL, c, line); break;
            case '/': token = new Token(Token::DIV, c, line); break;
            case '.': {
                if (current+1 < input.length() && input[current+1] == '.') {
                    token = new Token(Token::RANGE, "..", 0, 2, line);
                    current++;
                }
                else {
                    // Reserved for DOT
                }
                break;
            }
            case ',': token = new Token(Token::COMMA, c, line); break;
            case '(': token = new Token(Token::LPAR, c, line); break;
            case ')': token = new Token(Token::RPAR, c, line); break;
            case '{': token = new Token(Token::LBRACKET, c, line); break;
            case '}': token = new Token(Token::RBRACKET, c, line); break;
            case '=': {
                if (current+1 < input.length() && input[current+1] == '=') {
                    token = new Token(Token::EQUALS, "==", 0, 2, line);
                    current++;
                }
                else {
                    token = new Token(Token::ASSIGN, c, line);
                }
                break;
            }
            case '<': {
                if (current+1 < input.length() && input[current+1] == '=') {
                    token = new Token(Token::LESS_EQ, "<=", 0, 2, line);
                    current++;
                } else {
                    token = new Token(Token::LESS, c, line);
                }
                break;
            }
            case '>': {
                if (current+1 < input.length() && input[current+1] == '=') {
                    token = new Token(Token::GREATER_EQ, ">=", 0, 2, line);
                    current++;
                } else {
                    token = new Token(Token::GREATER, c, line);
                }
                break;
            }
            case '!': {
                if (current+1 < input.length() && input[current+1] == '=') {
                    token = new Token(Token::NEQUALS, "!=", 0, 2, line);
                    current++;
                } else {
                    // Reserved for NOT
                }
                break;
            }
            case ';': token = new Token(Token::SEMICOLON, c, line); break;
            default: {
                cout << "No debería llegar acá\n";
                token = new Token(Token::ERR, c, line);
            }
        }
        current++;
    }
    else {
        token = new Token(Token::ERR, c, line);
        current++;
    }
    return token;
}