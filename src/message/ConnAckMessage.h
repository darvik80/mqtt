//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_CONNACKMESSAGE_H
#define MQTT_CONNACKMESSAGE_H

#include <message/Message.h>

namespace mqtt::message {

    class ConnAckMessage : public Message {
    private:
        union {
            uint8_t all;    /**< all connack flags */
            struct {
                bool sessionPresent : 1;    /**< was a session found on the server? */
                unsigned int reserved : 7;    /**< message type nibble */
            } bits;
        } _flags{};     /**< connack flags byte */
        uint8_t _rc{}; /**< connack reason code */
    public:
        [[nodiscard]] int getType() const override {
            return MQTT_MSG_CONNACK;
        }

        [[nodiscard]] uint8_t getReasonCode() const;

        void setReasonCode(uint8_t rc);


        [[nodiscard]] uint8_t getFlags() const;

        void setFlags(uint8_t rc);

    };

}


#endif //MQTT_CONNACKMESSAGE_H
