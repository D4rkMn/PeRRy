#include <iostream>
#include <cstring>

#include "P/Token/Token.h"
#include "P/Scanner/Scanner.h"
using namespace std;

P::Token* P::Scanner::nextToken() {
    
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

    // Numerical literal
    if (isdigit(c) || c == '-') {
        current++;
        while (current < input.length() && isdigit(input[current])) {
            current++;
        }
        return new Token(Token::NUM, input, first, current - first, line);
    }

    // Reserved keywords + Id
    if (isalpha(c)) {
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
        // Edge case: Labels
        if (isLabel(word)) {
            return new Token(Token::LABEL, word, 1, word.length(), line);
        }
        // Return identifier
        return new Token(Token::ID, word, 0, word.length(), line);
    }

    // Catch error case
    current++;
    return new Token(Token::ERR, c, line);
}