#pragma once

#include <network/network_model.h>

#include <cstdlib>
#include <memory>

namespace provider {

class ProviderModel {
public:
    ProviderModel();

    void exitApp();

    std::shared_ptr<network::NetworkModel> network();

private:
    std::shared_ptr<network::NetworkModel> networkPtr;    
};

}