#include "network/network_model.h"

#include <iostream>
#include <array>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <tuple>

#include <pcapplusplus/PcapLiveDeviceList.h>

namespace network {

bool NetworkModel::enableInterface(std::string& interface) {
    // уже включенные интерфейсы
    if (interfaces.find(interface) != interfaces.end()) {
        return false;
    }

    return interfaces.insert(interface).first != interfaces.end();
}

std::vector<std::deque<std::string>> NetworkModel::listOfInterfaces() {
    std::vector<std::deque<std::string>> interfaces;

    auto listInterfaces = pcpp::PcapLiveDeviceList::PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();

    std::for_each(listInterfaces.cbegin(), listInterfaces.cend(), [&interfaces](auto &interface) -> void {
        std::deque<std::string> lines;
        lines.emplace_back("Интерфейс:");
        lines.push_back(interface->getName());
        lines.emplace_back("Описание:");
        lines.push_back(interface->getDesc());
        lines.emplace_back("IPv4:");
        lines.push_back(interface->getIPv4Address().toString());
        interfaces.emplace_back(std::move(lines));
    });

    return interfaces;
}

} // namespace network
