#pragma once

#include <cstdint>

namespace network {

class Port {
public:
    Port() = delete;
    Port(uint32_t port);

private:
    uint32_t port;
};

} // namespace network
