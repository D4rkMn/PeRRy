#ifndef P_STACKOBJECT_H
#define P_STACKOBJECT_H

#include "P/Namespace.h"
#include <string>

class P::IStackObject {
public:
    enum Type {
        ADDRESS_OBJECT,
        VALUE_OBJECT
    };
    virtual ~IStackObject() = default;
    virtual Type getType() const = 0;
};

class P::AddressObject : public IStackObject {
public:
    std::string id;
    AddressObject(const std::string& id) : id(id) {}
    ~AddressObject() = default;
    Type getType() const override { return ADDRESS_OBJECT; }
};

class P::ValueObject : public IStackObject {
public:
    int64_t value;
    ValueObject(int64_t value) : value(value) {}
    ~ValueObject() = default;
    Type getType() const override { return VALUE_OBJECT; }
};

#endif