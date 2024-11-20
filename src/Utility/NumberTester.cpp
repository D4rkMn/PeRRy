#include "Utility/NumberTester.h"
#include <stdexcept>
#include <iostream>
#include <limits>
using namespace std;

bool NumberTester::hasTraillingWhitespace(const string& str) {
    size_t len = str.length();
    size_t i = len;
    while (i > 0 && isspace(static_cast<unsigned char>(str[i - 1]))) {
        --i;
    }
    return i < len;
}

bool NumberTester::isNumber(const string& numStr) {
    if (numStr.empty()) return false;
    if (NumberTester::hasTraillingWhitespace(numStr)) {
        return false;
    }
    size_t start = 0;
    if (numStr[0] == '-') {
        start = 1;
    }
    for (size_t i = start; i < numStr.size(); ++i) {
        if (!isdigit(numStr[i])) {
            return false;
        }
    }
    return true;
}

bool NumberTester::fitsInInt32(const string& numStr) {
    if (!NumberTester::isNumber(numStr)) {
        return false;
    }
    if (numStr.find('.') != std::string::npos) {
        return false;
    }
    try {
        int64_t value = stoll(numStr);
        return value >= numeric_limits<int32_t>::min() &&
                value <= numeric_limits<int32_t>::max();
    } catch (...) {
        return false;
    }
}

bool NumberTester::fitsInUInt32(const string& numStr) {
    if (!NumberTester::isNumber(numStr)) {
        return false;
    }
    if (!numStr.empty() && numStr[0] == '-') {
        return false;
    }
    if (numStr.find('.') != string::npos) {
        return false;
    }
    try {
        uint64_t value = stoull(numStr);
        return value <= numeric_limits<uint32_t>::max();
    } catch (...) {
        return false;
    }
}

bool NumberTester::fitsInInt64(const string& numStr) {
    if (!NumberTester::isNumber(numStr)) {
        return false;
    }
    if (numStr.find('.') != string::npos) {
        return false;
    }
    try {
        stoll(numStr);
        return true;
    } catch (const std::out_of_range&) {
        return false;
    } catch (...) {
        return false;
    }
}

bool NumberTester::fitsInUInt64(const string& numStr) {
    if (!NumberTester::isNumber(numStr)) {
        return false;
    }
    if (!numStr.empty() && numStr[0] == '-') {
        return false;
    }
    if (numStr.find('.') != string::npos) {
        return false;
    }
    try {
        stoull(numStr);
        return true;
    } catch (...) {
        return false;
    }
}