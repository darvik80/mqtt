//
// Created by Ivan Kishchenko on 05.09.2020.
//

#ifndef MQTT_PACKET_H
#define MQTT_PACKET_H

#include "Properties.h"

namespace mqtt {
    enum MqttMessageType {
        MQTT_MSG_RESERVED,
        MQTT_MSG_CONNECT,       // К* -> С**	    connection requests
        MQTT_MSG_CONNACK,       // К <- С	        connection confirmed
        MQTT_MSG_PUBLISH,       // К <- С, К -> С   publish msg
        MQTT_MSG_PUBACK,        // К <- С, К -> С   publish confirmed
        MQTT_MSG_PUBREC,        // К <- С, К -> С   publish received
        MQTT_MSG_PUBREL,        // К <- С, К -> С   msg can be deleted
        MQTT_MSG_PUBCOMP,       // К <- С, К -> С   publish finished
        MQTT_MSG_SUBSCRIBE,     // К -> С           request for subscribe
        MQTT_MSG_SUBACK,        // К <- С           subscribe confirmed
        MQTT_MSG_UNSUBSCRIBE,   // К -> С           request for unsubscribe
        MQTT_MSG_UNSUBACK,     // К <- С           unsubscribe confirmed
        MQTT_MSG_PINGREQ,       // К -> С           ping
        MQTT_MSG_PINGRESP,      // К <- С           pong
        MQTT_MSG_DISCONNECT,    // К -> С           disconnect
        MQTT_MSG_RESERVED_DONE
    };

    const char *mqttMsgName(uint8_t type);

    union Header {
        uint8_t all;
        struct {
            bool retain: 1;
            unsigned int qos: 2;    /**< QoS value, 0, 1 or 2 */
            bool dup: 1;            /**< DUP flag bit */
            unsigned int type: 4;    /**< message type nibble */
        } bits;
    };

    struct Flags {
        union {
            uint8_t all;

            struct {
                union {
                    int : 1;                    /**< unused */
                    bool cleanSession: 1;        /**< cleansession flag */
                    bool willFlag: 1;              /**< will flag */
                    unsigned int willQoS: 2;   /**< will QoS value */
                    bool willRetain: 1;        /**< will retain setting */
                    bool password: 1;          /**< 3.1 password */
                    bool username: 1;          /**< 3.1 user name */
                };
            } bits;
        };
    };
}

#endif //MQTT_PACKET_H
