#ifndef P_SCANNER_H
#define P_SCANNER_H

#include <string>
#include "P/Token/Token.h"
#include "P/Namespace.h"

class P::Scanner {
private:

    std::string input = "";
    size_t first = 0, current = 0, line = 1;
    bool isTestScanner = false;

    bool isWhiteSpace(char c) const;
    bool isNewline(char c) const;
    bool isLabel(const std::string&) const;

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

#endif