//
// Created by Ivan Kishchenko on 04.09.2020.
//

#ifndef MQTT_ENCODER_H
#define MQTT_ENCODER_H

#include <ostream>
#include <boost/endian.hpp>

namespace mqtt {
    class Encoder {
    private:
        template<typename T>
        size_t writeNumber(const T &val, std::ostream &out) {
            static_assert(std::is_integral<T>::value);

            T data = boost::endian::endian_reverse(val);
            out.write((const char *) &data, sizeof(T));

            return sizeof(T);
        };

    public:
        size_t writeInt8(int8_t val, std::ostream &out) {
            return writeNumber(val, out);
        };

        size_t writeInt16(int16_t val, std::ostream &out) {
            return writeNumber(val, out);
        };

        size_t writeInt32(int32_t val, std::ostream &out) {
            return writeNumber(val, out);
        };

        size_t writeInt64(int64_t val, std::ostream &out) {
            return writeNumber(val, out);
        };

        size_t writeUint8(uint8_t val, std::ostream &out) {
            return writeNumber(val, out);
        };

        size_t writeUint16(uint16_t val, std::ostream &out) {
            return writeNumber(val, out);
        };

        size_t writeUint32(uint32_t val, std::ostream &out) {
            return writeNumber(val, out);
        };

        size_t writeUint64(uint64_t val, std::ostream &out) {
            return writeNumber(val, out);
        };

        size_t writeString(std::string &val, std::ostream &out) {
            size_t ret = writeUint16((uint16_t) val.size(), out);
            out.write(val.data(), val.length());

            return ret + val.length();
        };

        size_t writeVariableInt(int val, std::ostream &inc) {
            size_t res = 0;
            do {
                uint8_t encoded = val % 0x80;
                val /= 0x80;
                if (val > 0) {
                    encoded |= 0x80;
                }

                res += writeUint8(encoded, inc);
            } while (val > 0);

            return res;
        }

    };

}

#endif //MQTT_ENCODER_H
