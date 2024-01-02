#pragma once
#include "Header.hpp"
#include "CompactArray.hpp"
#include "Component.hpp"
#include "Instruction.hpp"
#include "Solana/Core/Types/Types.hpp"

namespace Solana::Transaction {
    struct BlockHash : public Bytes<32> {
        fromStr(BlockHash, 32)
    };

    using AddressSection = CompactArray<Pubkey>;

    struct Message : public Component {

        Message(
            const Header & header,
            const AddressSection & addressSection,
            const BlockHash & blockHash,
            const CompactArray<CompiledInstruction> & instructions)
            : header(header)
            , addresses(addressSection)
            , recentBlockhash(blockHash)
            , instructions(instructions)
        {}

        bool operator==(const Message & other) const = default;

        Header header;
        AddressSection addresses;
        BlockHash recentBlockhash;
        CompactArray<CompiledInstruction> instructions;
        void serialize(Buffer & out) const override {
            header.serialize(out);
            addresses.serialize(out);
            recentBlockhash.serialize(out);
            instructions.serialize(out);
        }
    };
}
