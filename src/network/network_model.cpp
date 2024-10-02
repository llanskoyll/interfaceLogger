#include "network/network_model.h"

#include <iostream>
#include <array>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <tuple>

#include <pcapplusplus/PcapLiveDeviceList.h>

namespace network {

bool NetworkModel::setPort(portNum port) {
    // уже выбранные порты
    if (ports.find(port) != ports.end()) {
        return false;
    }

    // Наличие открытых портов вообще в системе
    if (alivePort.find(port) == alivePort.end()) {
        return false;
    }

    return ports.insert({port, Port(port)}).first != ports.end();
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
