#include "network/network_model.h"

#include <iostream>
#include <array>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <tuple>
#include <thread>
#include <atomic>

#ifdef __APPLE__
#include <PcapLiveDeviceList.h>
#else
#include <pcapplusplus/PcapLiveDeviceList.h>
#endif
#include <boost/asio/post.hpp>
#include <boost/thread/thread.hpp>

namespace network {

NetworkModel::NetworkModel()
    // 1 - интрефейс, 1 - Логгирование
    : countThread_(std::thread::hardware_concurrency() - 1 - 1)
    , threadPool_(countThread_)
{}

void NetworkModel::stopSniff() {
    for (auto& interface : interfaces_) {
        interface.stopSniff();
    }

    threadPool_.join();
    interfaces_.clear();
}

bool NetworkModel::enableInterface(std::string& interfaceName) {
    if (interfaces_.size() == countThread_) {
        return false;
    }

    // уже включенные интерфейсы
    if (interfaces_.find(interfaceName) != interfaces_.end()) {
        return false;
    }

    auto it = interfaces_.emplace(interfaceName);
    if (it.first == interfaces_.end()) {
        return false;
    };

    auto& interface = *it.first;
    boost::asio::post(threadPool_, [&interface]() -> void {
        interface.sniffing();
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
