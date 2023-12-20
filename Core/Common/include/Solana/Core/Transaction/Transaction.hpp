#pragma once
#include "Solana/Core/Types/Types.hpp"
#include <vector>

namespace Solana {
    class Transaction {
    public:
        using Signatures = std::vector<String<64>>;

    private:
        Signatures signatures;
    };
}


