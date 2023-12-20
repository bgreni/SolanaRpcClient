#pragma once

#include <string_view>
#include <string>
#include <optional>

// Slightly modified version of what's in the BTC core code

namespace Solana::Encoding::Base58 {
    std::string Encode(std::string_view input);
    std::optional<std::string> Decode(std::string_view input);
}

