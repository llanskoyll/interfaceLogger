#include "userInterface/cli.h"

#include <iostream>
#include <iomanip>

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
    auto interfaces = provider->network()->listOfInterfaces();

    clearConsole();
    printMessage(WARNING, "Информация о интерфейсах");
    int num = 1;
    std::cout << std::endl;
    std::for_each(interfaces.begin(), interfaces.end(), [this, &num](auto& deq) -> void {
        std::cout << std::left;
        std::string line;

        printMessage(SUCCESS, std::string("Номер:") + std::to_string(num));
        std::cout << std::setw(10);

        line = deq.front();
        printMessage(SUCCESS, line);
        deq.pop_front();
        
        line = deq.front();
        printMessage(ERROR, line);
        std::cout << std::setw(line.size() < 25 ? 25 - line.size() : 1);
        deq.pop_front();

        line = deq.front();
        printMessage(SUCCESS, line);
        deq.pop_front();

        line = deq.front();
        printMessage(ERROR, line);
        std::cout << std::setw(line.size() < 60 ? 60 - line.size() : 1);
        deq.pop_front();

        line = deq.front();
        printMessage(SUCCESS, line);
        deq.pop_front();

        line = deq.front();
        printMessage(ERROR, line);

        std::cout << std::endl;
    });
}

} // namespace interface
