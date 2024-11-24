#ifndef R_ENVIRONMENT_H
#define R_ENVIRONMENT_H

#include <unordered_map>
#include <optional>
#include <vector>
#include <string>
#include "R/Namespace.h"

template <typename T>
class R::Environment {
protected:

    std::vector< std::unordered_map<std::string, T> > ribs;
    int searchRib(const std::string& var) const;

public:

    Environment() = default;
    ~Environment() = default;

    virtual void clear();
    void addLevel();
    virtual bool removeLevel();

    void addVariable(const std::string&);
    void addVariable(const std::string&, const T&);
    bool updateVariableValue(const std::string&, const T&);

    size_t getVariableLevel(const std::string&) const;
    bool checkVariableExists(const std::string&) const;
    std::optional<T> getVariableValue(const std::string&) const;
};

#include "R/Environment/Environment.tpp"

#endif