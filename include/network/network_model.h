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
    NetworkModel() = default;
    ~NetworkModel() = default;

    bool enableInterface(std::string& interface);

    std::vector<std::deque<std::string>> listOfInterfaces();

private:
    std::unordered_set<std::string> interfaces;
};

} // namespace network
    