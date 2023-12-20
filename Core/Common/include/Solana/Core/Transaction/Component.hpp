#pragma once
#include <vector>

namespace Solana::Transaction {
    struct Component {
        virtual void serialize(std::vector<unsigned char> & out) const = 0;
    };
}
