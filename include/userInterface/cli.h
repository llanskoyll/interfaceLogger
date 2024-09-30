#pragma once

#include <unordered_map>
#include <functional>
#include <string>

namespace interface {

class CLI {
public:
    CLI();
    int execute();

private:
    int menuShow();
    void printComponents();
    int executeComponents(std::string &command);

    int exit();

private:
    typedef enum {
        EXIT = 0
    } components;

    std::unordered_map<components, std::function<int()>> funComponents;
    std::unordered_map<components, std::string> menuComponents;
};

} // namespace interface
