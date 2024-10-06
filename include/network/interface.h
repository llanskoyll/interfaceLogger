#pragma once

#include <iostream>

#ifdef __APPLE__
#include <PcapLiveDeviceList.h>
#else
#include <pcapplusplus/PcapLiveDeviceList.h>
#endif

namespace network { namespace interface {

class Interface {
public:
    using portNum = uint32_t;

    Interface() = delete;
    Interface(std::string &interface);

    bool operator==(const Interface& other) const;
    
    std::string getName() const;
    void stopSniff() const;

    void sniffing() const;

private:
    std::string uint8_vector_to_hex_string(const std::vector<uint8_t>& v) const;

private:
    pcpp::PcapLiveDevice *device;
    mutable pcpp::PcapLiveDevice::PcapStats stats;
};


struct InterfaceHash {
    std::size_t operator()(const Interface& Interface) const {
        return std::hash<std::string>()(Interface.getName()); 
    }
};

struct InterfaceEq {
    bool operator()(const Interface& lhs, const Interface& rhs) const {
        return lhs == rhs;
    }
};

}  } // namespace network::interface
