#include "network/network_model.h"

namespace network {

bool NetworkModel::setPort(uint32_t port) {
    return ports.insert({port, Port(port)}).first != ports.end();
}

}