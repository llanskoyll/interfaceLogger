#include "network/network_model.h"

#include <iostream>
#include <array>
#include <cstdio>
#include <memory>

namespace network {

bool NetworkModel::setPort(uint32_t port) {
    if (ports.find(port) != ports.end()) {
        return false;
    }

    return ports.insert({port, Port(port)}).first != ports.end();
}

std::string NetworkModel::listOpenPortsInSystem() {
    std::string ports;

    std::array<char, 128> buffer;
    std::string port;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("ss -tuln", "r"), pclose);
    if (!pipe) {
        std::cerr << "Не удалось получить список открытых портов" << std::endl;
        exit(1);
    }

    while (std::fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        ports += buffer.data();
    }

    return ports;
}

}