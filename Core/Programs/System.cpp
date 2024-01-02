//
// Created by Brian Grenier on 2023-12-21.
//

#include "Solana/Core/Programs/System/System.hpp"

using namespace Solana;

namespace {
    const Pubkey ProgramId = Pubkey::fromString("11111111111111111111111111111111");
}

Solana::Transaction::Instruction Solana::Programs::System::Transfer::toInstruction() const {

    return Solana::Transaction::Instruction {
        .programId = ProgramId,
        .accounts = Transaction::CompactArray<Transaction::Account>{
            fromAccount,
            toAccount
        },
        .data = data.encode()
    };
}
