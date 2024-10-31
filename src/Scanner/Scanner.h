#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include "Token/Token.h"

class Scanner {
private:

    std::string input;
    size_t first, current;

    bool isWhiteSpace(char c) const;

public:

    Scanner(const char* in_s);
    ~Scanner();

    void test() const;
  
    Token* nextToken();
    void reset();

};

#endif // SCANNER_H