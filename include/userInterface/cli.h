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
        SET_PORT = 0,
        REMOVE_PORT,
        RUN_SCANNING,
        STOP_SCANNING,
        ENABLE_LOG,
        DISABLE_LOG,
        EXIT,
    } components;

    int menuShow();
    void printComponents();
    void printMessage(messageType type, std::string message);
    void executeComponents(components component);
    void clearConsole();

    void exit();
    void setPort();

private:
    std::unordered_map<components, std::function<void()>> funComponents;
    std::map<components, std::string> menuComponents;

    std::unique_ptr<provider::ProviderModel> provider;
};

} // namespace interface
