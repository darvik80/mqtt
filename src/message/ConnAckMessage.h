//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_CONNACKMESSAGE_H
#define MQTT_CONNACKMESSAGE_H

#include <message/Message.h>

namespace mqtt::message {
    enum ConnRespCode {
        RESP_CODE_ACCEPTED,                         // DefaultConnection accepted
        RESP_CODE_UNACCEPTABLE_PROTOCOL_VERSION,    // DefaultConnection refused, unacceptable protocol version
        RESP_CODE_IDENTIFIER_REJECTED,              // DefaultConnection refused, identifier rejected
        RESP_CODE_SERVER_UNAVAILABLE,               // DefaultConnection refused, server unavailable
        RESP_CODE_BAD_USER_NAME_OR_PASSWORD,        // DefaultConnection refused, bad user name or password
        RESP_CODE_NOT_AUTHORIZED,                   // DefaultConnection refused, not authorized
    };

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
        ConnAckMessage() : Message(MQTT_MSG_CONNACK){ }

        [[nodiscard]] uint8_t getReasonCode() const;
        const char* getReasonCodeDescription() const;

        void setReasonCode(uint8_t rc);


        [[nodiscard]] uint8_t getFlags() const;

        void setFlags(uint8_t rc);

    };

}


#endif //MQTT_CONNACKMESSAGE_H
