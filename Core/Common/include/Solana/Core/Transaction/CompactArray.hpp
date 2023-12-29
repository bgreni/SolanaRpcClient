#pragma once
#include "Solana/Core/Types/Types.hpp"
#include <array>
#include "Component.hpp"
#include <type_traits>

namespace Solana::Transaction {

    template<typename T = unsigned char>
    class CompactArray :
        public std::vector<T>,
        public Component
    {
        public:
            void serialize(Buffer & out) const override {
                u16 lenBits = 0;
                u16 Length = this->size();
                if (Length > 0x3FFF) {
                    u8 topTwo = (Length & 0x6000) >> 14;
                    out.push_back(0xFF);
                    out.push_back(0xFF);
                    out.push_back(topTwo);
                } else {
                    if (Length <= MASK){
                        lenBits = Length & MASK;
                    } else {
                        lenBits = 0xFF;
                        auto nextSeven = Length & MID_SEVEN;
                        lenBits += nextSeven;
                    }
                    out.push_back(Length & 0xFF);
                    out.push_back((Length >> 8) & 0xFF);
                }

                if constexpr (std::is_same_v<T, unsigned char>) {
                    for (auto el : *this) {
                        out.push_back(el);
                    }
                } else {
                    for (auto & el : *this) {
                        el.serialize(out);
                    }
                }
            }
    private:
        static constexpr u8 MASK = 0x7F;
        static constexpr u16 MID_SEVEN = 0x1F80;
    };
}
