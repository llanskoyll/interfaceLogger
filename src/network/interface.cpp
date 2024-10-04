#include <network/interface.h>

#include <unistd.h>

namespace network::interface {

Interface::Interface(std::string &interface) {
    name_ = interface; 
    sniffing_.store(true);
}

std::string Interface::getName() const {
    return name_;
}

void Interface::stopSniff() const {
    sniffing_.store(false);
}

void Interface::sniffing() const {
    sniffing_.store(true);

    while (sniffing_.load()) {
        sleep(1);
        std::cout << "thread\n";
    }
}
} // namespace network::interface