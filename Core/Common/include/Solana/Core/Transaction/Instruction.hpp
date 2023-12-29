#pragma once
#include "Component.hpp"
#include "CompactArray.hpp"

namespace Solana::Transaction {

    struct Account {
        Pubkey key;
        bool isSigner;
        bool isWritable;
    };

    struct Instruction : public Component {
        Pubkey programId;
        CompactArray<Account> accounts;
        u32 number;

        void serialize(Buffer &out) const override {
            serializeData(out);
        }
    private:
        virtual void serializeData(Buffer & out) const = 0;
    };
}