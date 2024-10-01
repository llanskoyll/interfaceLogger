#include <userInterface/provider_model.h>

namespace provider {

ProviderModel::ProviderModel() {
    networkPtr = std::make_shared<network::NetworkModel>();
}

void ProviderModel::exitApp() {
    int code = 0;
    // something things
    exit(code);
}

std::shared_ptr<network::NetworkModel> ProviderModel::network() {
    return networkPtr;
}

}