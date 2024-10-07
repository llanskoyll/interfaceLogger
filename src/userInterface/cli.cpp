#include "userInterface/cli.h"

#include <iostream>
#include <iomanip>

namespace interface {

CLI::CLI()
    : provider_(std::make_unique<provider::ProviderModel>())
{
    funComponents_.insert({ENABLE_INTERFACE, std::bind(&CLI::enableInterface, this)});
    funComponents_.insert({EXIT, std::bind(&CLI::exit, this)});
    funComponents_.insert({DISABLE_INTERFACES, std::bind(&CLI::disableIntrefaces, this)});

    menuComponents_.insert({EXIT, "Выход"});
    menuComponents_.insert({ENABLE_INTERFACE, "Установить интерфейс"});
    menuComponents_.insert({DISABLE_INTERFACES, "Остановить прослушивания интерфейсов"});
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
    for (auto& [component, line] : menuComponents_) {
        std::cout << "Введите: " << component << " - для испольнения " << line << std::endl;
    }
}       

void CLI::executeComponents(components component) {
    funComponents_.find(component)->second();
}

void CLI::exit() {
    provider_->exitApp();
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

void CLI::enableInterface() {
    auto interfaces = provider_->network()->listOfInterfaces();
    std::string in;
    auto interface = printInterfaces(interfaces);

    printMessage(WARNING, "Введите номер интерфейса: ");
    std::cin >> in;

    auto line = interface[std::stoi(in) - 1];

    std::string path("log/log.txt"); // TODO: Условный путь для файлова логов
    if (!line.empty() && provider_->network()->enableInterface(line, path)) {
        printMessage(SUCCESS, "Интерфейс установлен");
    } else {
        printMessage(ERROR, "Не удалось установить интерфейс");
    }

    std::cout << std::endl;
    return;
}

void CLI::disableIntrefaces() {
    provider_->network()->stopSniff();
}

std::vector<std::string> CLI::printInterfaces(std::vector<std::deque<std::string>> &interfaces) {
    std::vector<std::string> interface;
    clearConsole();
    printMessage(WARNING, "Информация о интерфейсах");
    int num = 1;
    std::cout << std::endl;
    std::for_each(interfaces.begin(), interfaces.end(), [this, &num, &interface](auto& deq) -> void {
        std::cout << std::left;
        std::string line;

        line = std::string("Номер:") + std::to_string(num);
        printMessage(SUCCESS, line);
        std::cout << std::setw(line.size() < 22 ? 22 - line.size() : 1);

        line = deq.front();
        printMessage(SUCCESS, line);
        deq.pop_front();
        
        line = deq.front();
        printMessage(ERROR, line);
        std::cout << std::setw(line.size() < 25 ? 25 - line.size() : 1);
        interface.push_back(line);
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
        ++num;
    });

    return interface;
}

} // namespace interface
