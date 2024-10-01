#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>

#include <network/port.h>

namespace network {

class NetworkModel {
public:
    NetworkModel() = default;
    ~NetworkModel() = default;

    bool setPort(uint32_t port);

    std::string listOpenPortsInSystem();

private:
    std::unordered_map<uint32_t, Port> ports;
};

} // namespace network
    