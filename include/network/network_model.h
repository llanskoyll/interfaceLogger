#pragma once

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <deque>

#include <network/interface.h>
#include <log/log.h>

#include <boost/asio/thread_pool.hpp>

namespace network {

class NetworkModel {
public:
    NetworkModel();
    ~NetworkModel() = default;

    bool enableInterface(std::string& interface, std::string &pathSave);

    std::vector<std::deque<std::string>> listOfInterfaces();

    void stopSniff();

private:
    std::unordered_map<interface::Interface, std::shared_ptr<log::Log>,
                       interface::InterfaceHash, interface::InterfaceEq> interfaces_;

    std::size_t countThread_;
    boost::asio::thread_pool threadPool_;
};

} // namespace network
    