#pragma once

#include <cstdint>

namespace network {

class Port {
public:
    using portNum = uint32_t;

    Port() = delete;
    Port(portNum port);

private:
    portNum port;
};

} // namespace network
