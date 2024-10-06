#include <network/interface.h>

#include <unistd.h>
#include <sstream>
#include <iomanip>

#ifdef __APPLE__
#include <SystemUtils.h>
#else
#include <pcapplusplus/SystemUtils.h>
#endif


namespace network::interface {

Interface::Interface(std::string &interface) {
    device = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByName(interface); 
    if (device == nullptr) {
        std::cerr << "Cannot not find interface with" << std::endl;
        exit(1);
    }
}

std::string Interface::getName() const {
    return device->getName();
}

bool Interface::operator==(const Interface& other) const {
    return device->getName() == other.getName();
}

void Interface::stopSniff() const {
    device->stopCapture();
}

void Interface::sniffing() const {
    if (!device->open()) {
        std::cerr << "Cannot open device" << std::endl;
    }

    device->startCapture([this](pcpp::RawPacket *pPacket, pcpp::PcapLiveDevice *pDeivce, void *cookie) -> bool {
        pcpp::Packet packet(pPacket);

        pcpp::Layer* layer;

        if (packet.isPacketOfType(pcpp::Ethernet)) {
            layer = packet.getLayerOfType(pcpp::Ethernet);
        } else if (packet.isPacketOfType(pcpp::IPv4)) {
            layer = packet.getLayerOfType(pcpp::IPv4);
        } else if (packet.isPacketOfType(pcpp::IPv6)) {
            layer = packet.getLayerOfType(pcpp::IPv6);
        } else if (packet.isPacketOfType(pcpp::UnknownProtocol)) {
            return true;
        }

        std::string infoAboutIp = layer->toString();
        std::vector<uint8_t> log;

        for (auto ch : infoAboutIp) {
            log.push_back(ch);
        }

        std::vector<uint8_t> data(layer->getDataLen());
        layer->copyData(data.data());

        // TODO: обработка данных и логгирование
        std::cout << log.data() << " Данные: " << uint8_vector_to_hex_string(data) << std::endl;

        return true;
    }, static_cast<void *>(&stats));
}

std::string Interface::uint8_vector_to_hex_string(const std::vector<uint8_t>& v) const {
    std::string result;
    result.reserve(v.size() * 2);

    static constexpr char hex[] = "0123456789ABCDEF";

    for (uint8_t c : v)
    {
        result.push_back(hex[c / 16]);
        result.push_back(hex[c % 16]);
    }

    return result;
}

} // namespace network::interface
