#include "userInterface/cli.h"

#include <iostream>

namespace interface {

CLI::CLI()
    : provider(std::make_unique<provider::ProviderModel>())
{
    funComponents.insert({EXIT, std::bind(&CLI::exit, this)});
    funComponents.insert({SET_PORT, std::bind(&CLI::setPort, this)});

    menuComponents.insert({EXIT, "Выход"});
    menuComponents.insert({SET_PORT, "Установить порт"});
}

int CLI::execute() {
    return menuShow();
}

int CLI::menuShow() {
    std::string input;
    int code;

    clearConsole();
    while (true) {
        try {
            printComponents();
            std::cin >> input;
            // Парсинг ввода
            auto component = static_cast<components>(std::stoi(input));
            executeComponents(component);
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            return 1;
        }
    }

    return 0;
}

void CLI::clearConsole() {
    std::cout << "\x1B[2J\x1B[H" << std::endl;
}
void CLI::printComponents() {
    for (auto& [component, line] : menuComponents) {
        std::cout << "Введите: " << component << " - для испольнения " << line << std::endl;
    }
}       

void CLI::executeComponents(components component) {
    funComponents.find(component)->second();
}

void CLI::exit() {
    provider->exitApp();
}

void CLI::printMessage(messageType type, std::string message) {
    std::string start;
    std::string end;
    switch (type) {
        case ERROR:
            start = "\033[1;31m";
            end = "\033[0m";
            break;
        case WARNING:
            start = "\033[1;33m";
            end = "\033[0m";
            break;
        case SUCCESS:
            start = "\033[1;32m";
            end = "\033[0m";
            break;
        case INVITE:
            start = "\033[1;34m";
            end = "\033[0m";
            break;
        default:
            break;
    }

    std::cout << start << message << end;
}

void CLI::setPort() {
    std::string portStr;
    std::string ports = provider->network()->listOpenPortsInSystem();

    clearConsole();
    printMessage(WARNING, "Список портов");
    std::cout << std::endl;
    printMessage(SUCCESS, ports);
    std::cout << std::endl;
    printMessage(INVITE, "Введите порт:");
    std::cin >> portStr;

    uint32_t port = std::stoul(portStr);
    if (!provider->network()->setPort(port)) {
        printMessage(WARNING, "Не удалось установить порт");
    } else {
        printMessage(SUCCESS, "Порт успешно установлен");
    }
    std::cout << std::endl;
}

} // namespace interface
