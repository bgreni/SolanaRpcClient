#pragma once
#include <vector>
#include "Solana/Core/Types/Types.hpp"

namespace Solana::Transaction {
    struct Component {
        bool operator==(const Component & other) const = default;
        virtual void serialize(Buffer & out) const = 0;
    };
}
