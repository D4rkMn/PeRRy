#include <iostream>
#include <cstring>

#include "Token/Token.h"
#include "Scanner/Scanner.h"

using namespace std;

Token* Scanner::nextToken() {
    Token* token;

    // Skip empty characters
    while (current < input.length() && isWhiteSpace(input[current])) {
        current++;
    }
    
    // End of file
    if (current >= input.length()) {
        return new Token(Token::END);
    }

    char c = input[current];
    first = current;

    // Integer literal
    if (isdigit(c)) {
        current++;
        while (current < input.length() && isdigit(input[current])) {
            current++;
        }
        return new Token(Token::INTEGER, input, first, current - first);
    }

    // Reserved keywords + Id
    if (isalpha(c)) {
        current++;
        while (current < input.length() && isalnum(input[current])) {
            current++;
        }
        string word = input.substr(first, current - first);
        // Fetch for reserved keywords
        Token::Type type = Token::wordToToken(word);
        if (type != Token::ERR) {
            return new Token(type, word, 0, word.length());
        }
        // Edge case: "println!"
        if (word == "println" && current < input.length() && input[current] == '!') {
            current++;
            return new Token(Token::PRINTLN, word, 0, word.length());
        }
        // Return identifier
        return new Token(Token::ID, word, 0, word.length());
    }

    // Text literals
    if (c == '"') {
        current++;
        while (current < input.length() && input[current] != '"') {
            current++;
        }
        if (current >= input.length()) {
            cout << "Error: String cerrado incorrectamente!" << endl;
            exit(1);
        }
        current++;
        string word = input.substr(first, current - first);
        return new Token(Token::TEXT, word, 1, word.length()-2);
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
            token = new Token(Token::DIV, c);
            current++;
        }
    }

    // Handle symbols
    if (strchr("+-*/(){}=;:.,<>!", c)) {
        switch(c) {
            case '+': {
                if (current+1 < input.length() && input[current+1] == '=') {
                    token = new Token(Token::ADVANCE, c); break;
                }
                else {
                    token = new Token(Token::PLUS, c);
                }
                break;
            }
            case '-': {
                if (current+1 < input.length() && input[current+1] == '>') {
                    token = new Token(Token::RARROW, "->", 0, 2);
                }
                else {
                    token = new Token(Token::MINUS, c);
                }
                break;
            }
            case '*': token = new Token(Token::MUL, c); break;
            case '/': token = new Token(Token::DIV, c); break;
            case '.': {
                if (current+1 < input.length() && input[current+1] == '.') {
                    token = new Token(Token::RANGE, "..", 0, 2);
                }
                else {
                    // Reserved for DOT
                }
                break;
            }
            case ',': token = new Token(Token::COMMA, c); break;
            case '(': token = new Token(Token::LPAR, c); break;
            case ')': token = new Token(Token::RPAR, c); break;
            case '{': token = new Token(Token::LBRACKET, c); break;
            case '}': token = new Token(Token::RBRACKET, c); break;
            case '=': {
                if (current+1 < input.length() && input[current+1] == '=') {
                    current++;
                    token = new Token(Token::EQUALS, "==", 0, 2);
                }
                else {
                    token = new Token(Token::ASSIGN, c);
                }
                break;
            }
            case '<': {
                if (current+1 < input.length() && input[current+1] == '=') {
                    token = new Token(Token::LESS_EQ, "<=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::LESS, c);
                }
                break;
            }
            case '>': {
                if (current+1 < input.length() && input[current+1] == '=') {
                    token = new Token(Token::GREATER_EQ, ">=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::GREATER, c);
                }
                break;
            }
            case '!': {
                if (current+1 < input.length() && input[current+1] == '=') {
                    token = new Token(Token::NEQUALS, "!=", 0, 2);
                    current++;
                } else {
                    // Reserved for NOT
                }
                break;
            }
            case ';': token = new Token(Token::SEMICOLON, c); break;
            case ':': token = new Token(Token::COLON, c); break;
            default: {
                cout << "No debería llegar acá" << endl;
                token = new Token(Token::ERR, c);
            }
        }
        current++;
    }
    else {
        token = new Token(Token::ERR, c);
        current++;
    }
    return token;
}