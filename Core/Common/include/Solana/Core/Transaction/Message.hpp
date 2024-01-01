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
    struct Message {

        bool operator==(const Message & other) const = default;

        Header header;
        CompactArray<Pubkey> addresses;
        BlockHash recentBlockhash;
        CompactArray<CompiledInstruction> instructions;
        void serialize(Buffer &out) const{
            header.serialize(out);
            addresses.serialize(out);
            recentBlockhash.serialize(out);
            instructions.serialize(out);
        }
    };
}
