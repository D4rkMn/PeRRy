#include "Environment/HeapEnvironment.h"
using namespace std;

template <typename T>
void HeapEnvironment<T>::clear() {
    while (removeLevel());
}

template <typename T>
bool HeapEnvironment<T>::removeLevel() {
    if (this->ribs.size() > 0) {
        for (auto it = this->ribs.back().begin(); it != this->ribs.back().end(); it++) {
            delete it->second;
        }
        this->ribs.pop_back();
        return true;
    }
    return false;
}