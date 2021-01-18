//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_MESSAGE_H
#define MQTT_MESSAGE_H

#include <memory>
#include "QoS.h"
#include "MessageType.h"

namespace mqtt::message {

    union Header {
        uint8_t all;
        struct {
            bool retain: 1;
            unsigned int qos: 2;    /**< QoS value, 0, 1 or 2 */
            bool dup: 1;            /**< DUP flag bit */
            unsigned int type: 4;    /**< message type nibble */
        } bits;
    };

    typedef union {
        uint8_t all;
        struct {
            int reserved: 1;                    /**< unused */
            bool cleanSession: 1;        /**< cleansession flag */
            bool willFlag: 1;              /**< will flag */
            unsigned int willQoS: 2;   /**< will QoS value */
            bool willRetain: 1;        /**< will retain setting */
            bool password: 1;          /**< 3.1 password */
            bool username: 1;          /**< 3.1 user name */
        } bits;
    } Flags;

    class Message {
    public:
        typedef std::shared_ptr<Message> Ptr;
        typedef std::unique_ptr<Message> AutoPtr;

    private:
        Header _header{};

        uint32_t _size{};
    public:
        explicit Message(uint8_t type);

        void setQos(uint8_t qos) {
            _header.bits.qos = qos;
        }

        [[nodiscard]] uint8_t getQos() const {
            return _header.bits.qos;
        }

        void setRetain(bool retain) {
            _header.bits.retain = retain;
        }

        [[nodiscard]] virtual uint8_t getType() const {
            return _header.bits.type;
        }

        [[nodiscard]] virtual const char *getTypeStr() const;

        [[nodiscard]] const Header &getHeader() const;

        void setHeader(uint8_t header);

        [[nodiscard]] uint32_t getSize() const;

        void setSize(uint32_t size);

        virtual ~Message() = default;
    };

}


#endif //MQTT_MESSAGE_H
