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
    : countThread_(std::thread::hardware_concurrency() - 1 - 1)
    , threadPool_(countThread_)
{}

void NetworkModel::stopSniff() {
    // for (auto& [interface, flag] : endFlags) {
    //     flag.store(true);
    // }

    threadPool_.join();
    interfaces_.clear();
}

bool NetworkModel::enableInterface(std::string& interface) {
    if (interfaces_.size() == countThread_) {
        return false;
    }

    // уже включенные интерфейсы
    if (interfaces_.find(interface) != interfaces_.end()) {
        return false;
    }

    if (interfaces_.emplace(interface).first == interfaces_.end()) {
        return false;
    };

    // auto& flag = (*iter).second;
    // boost::asio::post(threadPool, [&flag]() -> void {
    //     while (!flag.load()) {
    //         // sniffing interface and maybe logging
    //     }
    // });

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
