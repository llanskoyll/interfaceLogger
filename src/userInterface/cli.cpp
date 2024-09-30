#include "userInterface/cli.h"

#include <iostream>

namespace interface {

CLI::CLI() {
    funComponents.insert({EXIT, std::bind(&CLI::exit, this)});

    menuComponents.insert({EXIT, "Выход"});
}

int CLI::execute() {
    return menuShow();
}

int CLI::menuShow() {
    std::string input;
    int code;

    while (true) {
        try {
            printComponents();
            std::cin >> input;
            code = executeComponents(input);

            if (code == EXIT) {
                break;
            }

        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            return 1;
        }
    }

    return 0;
}

void CLI::printComponents() {
    std::cout << "\x1B[2J\x1B[H" << std::endl;
    for (auto& [component, line] : menuComponents) {
    std::cout << "\033[1;31m" << "Введите: " << component << "\033[0m";
        std::cout << " - для испольнения ";
        std::cout << "\033[1;32m" << line << "\033[0m";
    }
    std::cout << std::endl;
}       

int CLI::executeComponents(std::string &command) {

    // TODO: парсинг command

    components component = static_cast<components>(std::stoi(command));

    return funComponents.find(component)->second();
}

int CLI::exit() {
    // TODO: методы при закрытие приложения
    return 0;
}

} // namespace interface
