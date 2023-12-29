#pragma once

#include <string_view>
#include <string>
#include <optional>

// Slightly modified version of what's in the BTC core code

namespace Solana::Encoding {

    class Base58 {
    public:
        static std::string Encode(std::string_view input) {
            return Encode((const unsigned char *)input.data(),
                          (const unsigned char *)input.data() + input.size());
        }
        static std::optional<std::string> Decode(std::string_view input);
    private:
        static std::string Encode(const unsigned char* pbegin, const unsigned char* pend);
    };



}

