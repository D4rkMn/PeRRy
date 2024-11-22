#ifndef R_SCANNER_H
#define R_SCANNER_H

#include <string>
#include <stack>
#include "R/Token/Token.h"
#include "R/Namespace.h"

class R::ScannerMovement {
public:
    size_t first, current, line;
    ScannerMovement(size_t f, size_t c, size_t l) : first(f), current(c), line(l) {}
    ~ScannerMovement() = default;
};

class R::Scanner {
private:

    std::string input = "";
    size_t first = 0, current = 0, line = 0;
    bool isTestScanner = false;

    std::stack<R::ScannerMovement> history;

    bool isWhiteSpace(char c) const;
    bool isNewline(char c) const;

public:

    Scanner() = default;
    ~Scanner() = default;

    void test() const;
  
    void setInput(const std::string&);
    void resetInput();

    Token* nextToken();
    void backtrack();
    void reset();

};

#endif // SCANNER_H