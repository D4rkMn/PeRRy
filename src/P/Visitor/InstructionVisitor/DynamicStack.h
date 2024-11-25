#ifndef P_DYNAMICSTACK_H
#define P_DYNAMICSTACK_H

#include "P/Namespace.h"
#include "P/Visitor/InstructionVisitor/StackObject.h"
#include <stack>
#include <list>

template <typename T>
class P::DynamicStack {
private:

    std::stack<T> m_stack;
    std::list<T> garbage;

public:

    DynamicStack() = default;

    ~DynamicStack() {
        for (auto it = garbage.begin(); it != garbage.end(); it++) {
            if (*it) delete *it; 
        }
    }

    void push(const T& v) {
        m_stack.push(v);
    }

    void pop() {
        garbage.push_back(m_stack.top());
        m_stack.pop();
    }

    T top() {
        return m_stack.top();
    }

    size_t size() const {
        return m_stack.size();
    }

    bool empty() const {
        return m_stack.empty();
    }

};

#endif