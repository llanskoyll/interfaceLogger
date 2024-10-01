#pragma once

#include <cstdint>
#include <unordered_map>

#include <network/port.h>

namespace network {

class NetworkModel {
public:
    NetworkModel() = default;
    ~NetworkModel() = default;

    bool setPort(uint32_t port);

private:
    std::unordered_map<uint32_t, Port> ports;
};

} // namespace network
    