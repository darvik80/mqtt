//
// Created by Ivan Kishchenko on 03.10.2020.
//

#ifndef MQTT_MESSAGEPACKETIDENTIFIER_H
#define MQTT_MESSAGEPACKETIDENTIFIER_H


#include <cstdint>

namespace mqtt::message {
    class MessagePacketIdentifier {
    private:
        uint16_t _packetIdentifier{};
    public:
        [[nodiscard]] uint16_t getPacketIdentifier() const {
            return _packetIdentifier;
        }

        void setPacketIdentifier(uint16_t packetIdentifier) {
            _packetIdentifier = packetIdentifier;
        }
    };
}

#endif //MQTT_MESSAGEPACKETIDENTIFIER_H
