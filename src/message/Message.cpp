//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "Message.h"

namespace mqtt::message {
    const Header &Message::getHeader() const {
        return _header;
    }

}