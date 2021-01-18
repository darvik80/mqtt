//
// Created by Ivan Kishchenko on 29.12.2020.
//

#ifndef MQTT_MESSAGETYPE_H
#define MQTT_MESSAGETYPE_H

namespace mqtt::message {
    enum MessageType {
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

}

#endif //MQTT_MESSAGETYPE_H
