#pragma once
#include <vector>
#include "Solana/Core/Types/Types.hpp"

namespace Solana::Transaction {
    struct Component {
        virtual void serialize(Buffer & out) const = 0;
    };
}
