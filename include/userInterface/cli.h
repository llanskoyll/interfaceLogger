#pragma once

#include <userInterface/provider_model.h>

#include <unordered_map>
#include <map>
#include <functional>
#include <string>

namespace interface {

class CLI {
public:
    CLI();
    int execute();

private:
    typedef enum {
        ERROR = 0,
        WARNING,
        SUCCESS,
        INVITE,
    } messageType;

    typedef enum {
        ENABLE_INTERFACE = 0,
        EXIT,
    } components;

    int menuShow();
    void printComponents();
    void printMessage(messageType type, std::string message);
    void executeComponents(components component);
    void clearConsole();
    std::vector<std::string> printInterfaces(std::vector<std::deque<std::string>> &interfaces);

    void exit();
    void enableInterface();

private:
    std::unordered_map<components, std::function<void()>> funComponents;
    std::map<components, std::string> menuComponents;

    std::unique_ptr<provider::ProviderModel> provider;
};

} // namespace interface
