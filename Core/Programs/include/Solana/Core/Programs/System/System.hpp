#pragma once
#include "Solana/Core/Transaction/Instruction.hpp"
#include "Solana/Core/Account/Account.hpp"


namespace Solana::Programs::System {

    struct Transfer : public Transaction::ConcreteInstruction {

        LAYOUT(Data,
               (u32, number),
               (u64, lamports))

        Transfer(
            const Pubkey & from,
            const Pubkey & to,
            u64 lamports)
                : data(Data{.number=2, .lamports = lamports})
                , toAccount(Transaction::Account {
                        .key = to,
                        .isSigner = false,
                        .isWritable = true,
                })
                , fromAccount(Transaction::Account {
                        .key = from,
                        .isSigner = true,
                        .isWritable = true,
                }) {}

        Transaction::Instruction toInstruction() const override;

        Transaction::Account toAccount;
        Transaction::Account fromAccount;
        Data data;
    };
};

