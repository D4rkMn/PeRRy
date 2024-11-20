#ifndef NUMBERTESTER_H
#define NUMBERTESTER_H

#include <string>

class NumberTester {
public:
    static bool hasTraillingWhitespace(const std::string&);
    static bool isNumber(const std::string&);
    static bool fitsInInt32(const std::string&);
    static bool fitsInInt64(const std::string&);
    static bool fitsInUInt32(const std::string&);
    static bool fitsInUInt64(const std::string&);
};

#endif