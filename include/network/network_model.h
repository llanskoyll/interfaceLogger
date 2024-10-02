#pragma once

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <deque>

#include <network/port.h>

namespace network {

class NetworkModel {
public:
    using portNum = Port::portNum;

    NetworkModel() = default;
    ~NetworkModel() = default;

    bool setPort(portNum port);

    std::vector<std::deque<std::string>> listOfInterfaces();

private:
    std::unordered_set<portNum> alivePort;
    std::unordered_map<portNum, Port> ports;
    std::unordered_map<std::string, portNum> interfaces;
};

} // namespace network
    