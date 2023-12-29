#pragma once
#include "Header.hpp"
#include "CompactArray.hpp"
#include "Component.hpp"
#include "Instruction.hpp"
#include "Solana/Core/Types/Types.hpp"

namespace Solana::Transaction {
    using BlockHash = Bytes<32>;
    struct Message : public Component {

        using Addresses = CompactArray<Pubkey>;
        struct AddressSection : public Component {
            Addresses readWrite;
            Addresses readOnly;

            void serialize(Buffer &out) const override {
                readWrite.serialize(out);
                readOnly.serialize(out);
            }
        };

        Header header;
        AddressSection requiresSig;
        AddressSection noSig;
        BlockHash recentBlockhash;
        CompactArray<Instruction> instructions;
        void serialize(Buffer &out) const override {
            header.serialize(out);
            requiresSig.serialize(out);
            noSig.serialize(out);
            recentBlockhash.serialize(out);
            instructions.serialize(out);
        }

    };
}
