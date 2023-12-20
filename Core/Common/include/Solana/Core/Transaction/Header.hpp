#pragma once

#include "Solana/Core/Types/Types.hpp"
#include "Component.hpp"

namespace Solana::Transaction {
    struct Header : public Component {
        u8 requiredSigs;
        u8 readOnlyAddresses;
        u8 readOnlyAddressNoSig;

        void serialize(std::vector<unsigned char> & out) const override {
            out.push_back(requiredSigs);
            out.push_back(readOnlyAddresses);
            out.push_back(readOnlyAddressNoSig);
        }
    };
}