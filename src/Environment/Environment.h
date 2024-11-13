#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <unordered_map>
#include <optional>
#include <vector>
#include <string>

template <typename T>
class Environment {
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

    bool checkVariableExists(const std::string&) const;
    std::optional<T> getVariableValue(const std::string&) const;
};

#include "Environment/Environment.tpp"

#endif