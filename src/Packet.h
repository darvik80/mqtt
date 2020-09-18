//
// Created by Ivan Kishchenko on 05.09.2020.
//

#ifndef MQTT_PACKET_H
#define MQTT_PACKET_H

#include "Properties.h"

namespace mqtt {
    enum MQTT_MSG_TYPE {
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

    union Header {
        uint8_t all;
        struct {
            bool dup: 1;            /**< DUP flag bit */
            unsigned int qos: 2;    /**< QoS value, 0, 1 or 2 */
            bool retain: 1;
            unsigned int type: 4;    /**< message type nibble */
        } bits;
    };

    struct Packet {
        Header header;    /**< MQTT header byte */
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


    struct Connect {
        Header header;    /**< MQTT header byte */

        //Bits flags;

        char *Protocol;     /**< MQTT protocol name */
        char *clientID;        /**< string client id */
        char *willTopic;    /**< will topic */
        char *willMsg;        /**< will payload */

        uint16_t keepAliveTimer;        /**< keepalive timeout value in seconds */
        uint8_t version;    /**< MQTT version number */
    };

    /**
     * Data for a connack packet.
     */
    struct ConnAck {
        Header header; /**< MQTT header byte */
        union {
            uint8_t all;    /**< all connack flags */
            struct {
                bool sessionPresent: 1;    /**< was a session found on the server? */
                unsigned int reserved: 7;    /**< message type nibble */
            } bits;
        } flags;     /**< connack flags byte */
        uint8_t rc; /**< connack reason code */
        uint16_t MQTTVersion;  /**< the version of MQTT */
        //Properties properties; /**< MQTT 5.0 properties.  Not used for MQTT < 5.0 */
    };


    /**
     * Data for a suback packet.
     */
    struct SubAck {
        Header header;    /**< MQTT header byte */
        int msgId;        /**< MQTT message id */
        int version;  /**< the version of MQTT */
        Properties properties; /**< MQTT 5.0 properties.  Not used for MQTT < 5.0 */
        //List *qoss;        /**< list of granted QoSs (MQTT 3/4) / reason codes (MQTT 5) */
    };


/**
 * Data for an MQTT V5 unsuback packet.
 */
    struct UnSubAck {
        Header header;    /**< MQTT header byte */
        int msgId;        /**< MQTT message id */
        int version;  /**< the version of MQTT */
        Properties properties; /**< MQTT 5.0 properties.  Not used for MQTT < 5.0 */
        //List *reasonCodes;    /**< list of reason codes */
    };
}


#endif //MQTT_PACKET_H
