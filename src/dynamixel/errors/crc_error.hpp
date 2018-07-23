#ifndef DYNAMIXEL_ERRORS_CRC_ERROR_HPP_
#define DYNAMIXEL_ERRORS_CRC_ERROR_HPP_

#include <string>
#include <stdint.h>
#include <sstream>

#include "error.hpp"

namespace dynamixel {
    namespace errors {
        /** @ingroup errors
        Triggered when the expected checksum and the received checksum do not match.
        **/
        class CrcError : public Error {
        public:
            CrcError(uint8_t id, uint8_t protocol, uint32_t expected, uint32_t received) : _id(id), _protocol(protocol), _expected(expected), _received(received)
            {
                std::stringstream err_message;
                err_message << "Status: checksum error while decoding packet with ID " << (int)id;
                err_message << std::hex << ": expected " << expected << ", received " << received;
                err_message << std::dec;
                this->_msg = err_message.str();
            }

            uint8_t id() const
            {
                return _id;
            }

            uint8_t protocol() const
            {
                return _protocol;
            }

            uint32_t expected() const
            {
                return _expected;
            }

            uint32_t received() const
            {
                return _received;
            }

        private:
            uint8_t _id, _protocol;
            uint32_t _expected, _received;
        };
    }
}

#endif
