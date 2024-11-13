#ifndef HEAPENVIRONMENT_H
#define HEAPENVIRONMENT_H

#include "Environment/Environment.h"

template <typename T>
class HeapEnvironment : public Environment<T> {
public:
    HeapEnvironment() = default;
    ~HeapEnvironment() { clear(); }

    void clear();
    bool removeLevel();
};

#include "Environment/HeapEnvironment.tpp"

#endif