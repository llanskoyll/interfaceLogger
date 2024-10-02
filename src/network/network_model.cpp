#include "network/network_model.h"

#include <iostream>
#include <array>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <tuple>
#include <thread>
#include <atomic>

#include <pcapplusplus/PcapLiveDeviceList.h>
#include <boost/asio/post.hpp>
#include <boost/thread/thread.hpp>

namespace network {

NetworkModel::NetworkModel()
    // 1 - интрефейс, 1 - Логгирование
    : threadPool(std::thread::hardware_concurrency() - 1 - 1)
{}

void NetworkModel::stopSniff() {
    for (auto& [interface, flag] : endFlags) {
        flag.store(true);
    }

    threadPool.join();
}

bool NetworkModel::enableInterface(std::string& interface) {
    // уже включенные интерфейсы
    if (interfaces.find(interface) != interfaces.end()) {
        return false;
    }

    if (interfaces.insert(interface).first == interfaces.end()) {
        return false;
    };

    auto iter = endFlags.emplace(interface, false).first;
    if (iter == endFlags.end()) {
        return false;
    }

    auto& flag = (*iter).second;
    boost::asio::post(threadPool, [&flag]() -> void {
        while (!flag.load()) {
            // sniffing interface and maybe logging
        }
    });

    return true;
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
