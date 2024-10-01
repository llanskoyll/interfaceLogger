#include "network/network_model.h"

#include <iostream>
#include <array>
#include <cstdio>
#include <memory>
#include <algorithm>

namespace network {

bool NetworkModel::setPort(uint32_t port) {
    if (ports.find(port) != ports.end()) {
        return false;
    }

    return ports.insert({port, Port(port)}).first != ports.end();
}

std::string NetworkModel::listOpenPortsInSystem() {
    std::vector<std::string> ports;
    std::vector<std::string> protocols;
    std::string result;

    std::array<char, 64> buffer;
    std::string port;
    std::string command("ss -tuln | awk '{print $1, $5}' | grep -oE '[A-Za-z]+|:[0-9]+'");

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.data(), "r"), pclose);
    if (!pipe) {
        std::cerr << "Не удалось получить список открытых портов" << std::endl;
        exit(1);
    }

    while (std::fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        std::string line(buffer.data());

        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());

        if (line.find(":") != std::string::npos) {
            ports.push_back(line.substr(1));
        } else {
            protocols.push_back(line);
        }
    }

    for (size_t i = 0; i < protocols.size() && i < ports.size(); ++i) {
        result += protocols[i];
        result += " ";
        result += ports[i];
        result += "\n";
    }

    return result;
}

} // namespace network
