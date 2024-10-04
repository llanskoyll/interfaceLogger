#pragma once

#include <iostream>
#include <atomic>

namespace network { namespace interface {

class Interface {
public:
    using portNum = uint32_t;

    Interface() = delete;
    Interface(std::string &interface);

    bool operator==(const Interface& other) const {
        return name_ == other.getName();
    };
    
    std::string getName() const;
    void stopSniff();

    void sniffing() {
        // ...sniff
    };
 
private:
    std::string name_;
    std::atomic<bool> sniffing_;
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
