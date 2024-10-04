#include <network/interface.h>

namespace network::interface {

Interface::Interface(std::string &interface) {
    name_ = interface; 
    sniffing_.store(true);
}

std::string Interface::getName() const {
    return name_;
}

void Interface::stopSniff() {
    sniffing_.store(false);
}

} // namespace network::interface