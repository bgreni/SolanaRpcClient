#pragma once
#include "Solana/Core/Types/Types.hpp"
#include <array>
#include "Component.hpp"

namespace Solana::Transaction {
    template<u16 Length>
    class CompactArray :
        public std::array<unsigned char, Length>,
        public Component
    {
        public:
            void serialize(std::vector<unsigned char> & out) const override {
                u16 lenBits = 0;

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


            }
    private:
        static constexpr u8 MASK = 0x7F;
        static constexpr u16 MID_SEVEN = 0x1F80;
    };
}
