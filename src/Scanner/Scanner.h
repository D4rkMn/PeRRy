#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <stack>
#include "Token/Token.h"

class ScannerMovement {
public:
    size_t first, current, line;
    ScannerMovement(size_t f, size_t c, size_t l) : first(f), current(c), line(l) {}
    ~ScannerMovement() = default;
};

class Scanner {
private:

    std::string input;
    size_t first, current, line;
    bool isTestScanner = false;

    std::stack<ScannerMovement> history;

    bool isWhiteSpace(char c) const;
    bool isNewline(char c) const;

public:

    Scanner(const char* in_s);
    ~Scanner();

    void test() const;
  
    Token* nextToken();
    void backtrack();
    void reset();

};

#endif // SCANNER_H