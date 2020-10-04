#include "Packet.h"

namespace mqtt {

    struct {
        MqttMessageType value;
        const char *name;
    } mqttNameToString[] = {
            {MQTT_MSG_RESERVED, "UNKNOWN"},
            {MQTT_MSG_CONNECT, "CONNECT"},
            {MQTT_MSG_CONNACK, "CONNACK"},
            {MQTT_MSG_PUBLISH, "PUBLICH"},
            {MQTT_MSG_PUBACK, "PUBACK"},
            {MQTT_MSG_PUBREC, "PUBREC"},
            {MQTT_MSG_PUBREL, "PUBREL"},
            {MQTT_MSG_PUBCOMP, "PUBCOMP"},
            {MQTT_MSG_SUBSCRIBE, "SUBSCRIBE"},
            {MQTT_MSG_SUBACK, "SUBACK"},
            {MQTT_MSG_UNSUBSCRIBE, "UNSUBSCRIBE"},
            {MQTT_MSG_UNSUBACK, "UNSUBACK"},
            {MQTT_MSG_PINGREQ, "PINGREQ"},
            {MQTT_MSG_PINGRESP, "PINGRESP"},
            {MQTT_MSG_DISCONNECT, "DISCONNECT"}

    };

    const char *mqttMsgName(uint8_t type) {
        return mqttNameToString[type].name;
    }
}