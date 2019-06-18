#ifndef DYNAMIXEL_INSTRUCTIONS_SYNC_WRITE_HPP_
#define DYNAMIXEL_INSTRUCTIONS_SYNC_WRITE_HPP_

#include <cassert>
#include <stdint.h>

#include "../errors/vector_size_errors.hpp"
#include "../instruction_packet.hpp"

namespace dynamixel {
    namespace instructions {
        template <class T>
        class SyncWrite : public InstructionPacket<T> {
        public:
            SyncWrite(typename T::address_t address, const std::vector<typename T::id_t>& ids,
                const std::vector<std::vector<uint8_t>>& data)
                : InstructionPacket<T>(T::broadcast_id, T::Instructions::sync_write, _get_parameters(address, ids, data)) {}

        protected:
            std::vector<uint8_t> _get_parameters(uint8_t address, const std::vector<typename T::id_t>& ids,
                const std::vector<std::vector<uint8_t>>& data)
            {
                if (ids.size() == 0)
                    throw errors::VectorEmptyError("SyncWrite", "ids");
                if (ids.size() != data.size())
                    throw errors::VectorSizesDifferError("SyncWrite", "ids", "data");

                typename T::length_t data_length = data[0].size();
                std::vector<uint8_t> parameters((data_length + 1) * ids.size() + 2);

                parameters[0] = address;
                parameters[1] = data_length;

                size_t curr = 2;

                for (size_t i = 0; i < ids.size(); ++i) {
                    if (data[i].size() != data_length)
                        throw errors::Error("SyncWrite: mismatch between declared"
                                            "data length and data vector size");
                    parameters[curr++] = ids[i];

                    for (size_t j = 0; j < data_length; ++j)
                        parameters[curr++] = data[i][j];
                }

                return parameters;
            }

            std::vector<uint8_t> _get_parameters(uint16_t address, const std::vector<typename T::id_t>& ids,
                const std::vector<std::vector<uint8_t>>& data)
            {
                if (ids.size() == 0)
                    throw errors::VectorEmptyError("SyncWrite", "ids");
                if (ids.size() != data.size())
                    throw errors::VectorSizesDifferError("SyncWrite", "ids", "data");

                typename T::length_t data_length = data[0].size();
                std::vector<uint8_t> parameters((data_length + 1) * ids.size() + 4);

                parameters[0] = (uint8_t)(address & 0xFF);
                parameters[1] = (uint8_t)((address >> 8) & 0xFF);
                parameters[2] = (uint8_t)(data_length & 0xFF);
                parameters[3] = (uint8_t)((data_length >> 8) & 0xFF);

                size_t curr = 4;

                for (size_t i = 0; i < ids.size(); ++i) {
                    if (data[i].size() != data_length)
                        throw errors::Error("SyncWrite: mismatch between declared"
                                            "data length and data vector size");
                    parameters[curr++] = ids[i];

                    for (size_t j = 0; j < data_length; ++j)
                        parameters[curr++] = data[i][j];
                }

                return parameters;
            }
        };
    } // namespace instructions
} // namespace dynamixel

#endif
