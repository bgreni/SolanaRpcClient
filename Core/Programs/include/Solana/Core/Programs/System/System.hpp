#pragma once
#include "Solana/Core/Transaction/Instruction.hpp"
#include "Solana/Core/Account/Account.hpp"


namespace Solana::Programs::System {

    const Pubkey ProgramId = Pubkey::fromString("11111111111111111111111111111111");

    struct Transfer : public Transaction::Instruction {

        LAYOUT(Data,
               (u64, lamports))

        Transfer(
            const Pubkey & to,
            const Pubkey & from,
            u64 lamports) : data(Data{.lamports = lamports}) {

            const auto toAccount = Transaction::Account {
                .key = to,
                .isSigner = false,
                .isWritable = true,
            };

            const auto fromAccount = Transaction::Account {
                .key = from,
                .isSigner = true,
                .isWritable = true,
            };
//             programId
        }
        Data data;
    };
};

