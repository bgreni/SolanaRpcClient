#pragma once

#include "Solana/Core/Types/Types.hpp"
#include "Component.hpp"

namespace Solana::Transaction {
    struct Header : public Component {
        bool operator==(const Header & other) const = default;

        u8 requiredSigs = 0;
        u8 readOnlyAddresses = 0;
        u8 readOnlyAddressNoSig = 0;

        void serialize(Buffer & out) const override {
            out.push_back(requiredSigs);
            out.push_back(readOnlyAddresses);
            out.push_back(readOnlyAddressNoSig);
        }
    };
}