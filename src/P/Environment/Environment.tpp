#include "P/Environment/Environment.h"
#include <iostream>
using namespace std;

template <typename T>
int P::Environment<T>::searchRib(const string& var) const {
    int idx = ribs.size() - 1;
    while (idx >= 0) {
        auto it = ribs.at(idx).find(var);
        if (it != ribs.at(idx).end()) {
            return idx;
        }
        idx--;
    }
    return -1;
}

template <typename T>
void P::Environment<T>::addLevel() {
    unordered_map<string, T> r;
    ribs.push_back(r);
}

template <typename T>
void P::Environment<T>::clear() {
    ribs.clear();
}

template <typename T>
void P::Environment<T>::addVariable(const string& var, const T& value) {
    if (ribs.size() == 0) {
        throw runtime_error("Error: Environment sin niveles - no se pueden agregar variables");
    }
    if (ribs.back().find(var) != ribs.back().end()) {
        throw runtime_error("Error: La variable ya ha sido declarada en este scope");
    }
    ribs.back().insert({var, value});
}

template <typename T>
void P::Environment<T>::addVariable(const string& var) {
    ribs.back()[var] = T{0};
}

template <typename T>
bool P::Environment<T>::removeLevel() {
    if (ribs.size() > 0) {
        ribs.pop_back();
        return true;
    }
    return false;
}

template <typename T>
bool P::Environment<T>::updateVariableValue(const string& x, const T& v) {
    int idx = searchRib(x);
    if (idx < 0) {
        return false;
    }
    ribs[idx][x] = v;
    return true;
}

template <typename T>
bool P::Environment<T>::checkVariableExists(const string& x) const {
    int idx = searchRib(x);
    return (idx >= 0);
}

template <typename T>
optional<T> P::Environment<T>::getVariableValue(const string& x) const {
    int idx = searchRib(x);
    if (idx < 0) {
        return nullopt;
    }
    return ribs.at(idx).at(x);
}