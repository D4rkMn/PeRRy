#ifndef R_NUMBERTESTER_H
#define R_NUMBERTESTER_H

#include <string>
#include "R/Namespace.h"

class R::NumberTester {
public:
    static bool hasTraillingWhitespace(const std::string&);
    static bool isNumber(const std::string&);
    static bool fitsInInt32(const std::string&);
    static bool fitsInInt64(const std::string&);
    static bool fitsInUInt32(const std::string&);
    static bool fitsInUInt64(const std::string&);
};

#endif