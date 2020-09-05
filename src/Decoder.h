//
// Created by Ivan Kishchenko on 05.09.2020.
//

#ifndef MQTT_DECODER_H
#define MQTT_DECODER_H

#include <istream>
#include <boost/endian.hpp>

#define MQTT_INVALID_INT_VALUE -1;

namespace mqtt {

    class Decoder {
    private:
        template<typename T>
        T readNumber(std::istream &inc) {
            static_assert(std::is_integral<T>::value);

            T res;
            inc.read((char *) &res, sizeof(T));

            return boost::endian::endian_reverse(res);
        };

    public:
        int8_t readInt8(std::istream &inc) {
            return readNumber<int8_t>(inc);
        }

        int16_t readInt16(std::istream &inc) {
            return readNumber<int16_t>(inc);
        }

        int32_t readInt32(std::istream &inc) {
            return readNumber<int32_t>(inc);
        }

        int64_t readInt64(std::istream &inc) {
            return readNumber<int64_t>(inc);
        }

        uint8_t readUint8(std::istream &inc) {
            return readNumber<int8_t>(inc);
        }

        uint16_t readUint16(std::istream &inc) {
            return readNumber<int16_t>(inc);
        }

        uint32_t readUint32(std::istream &inc) {
            return readNumber<int32_t>(inc);
        }

        uint64_t readUint64(std::istream &inc) {
            return readNumber<int64_t>(inc);
        }

        std::string readString(std::istream &inc) {
            std::string res;
            res.resize(readUint16(inc));

            inc.read(res.data(), res.size());

            return res;
        }

        int readVariableInt(std::istream &inc) {
            int multiplier = 1;
            int result = 0;

            uint8_t encoded = 0;
            do {
                encoded = readUint8(inc);
                result += (encoded & 0x7F) * multiplier;
                if (multiplier > 0x80 * 0x80 * 0x80) {
                    return MQTT_INVALID_INT_VALUE;
                }
                multiplier *= 0x80;
            } while ((encoded & 0x80) != 0);

            return result;
        }
    };

}

#endif //MQTT_DECODER_H
